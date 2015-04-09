/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/MapManager/AStarPathFinder.hpp"

#include <set>
#include <vector>

#include <QList>
#include <QDebug>
#include <QPair>
#include <QPointF>
#include <QSet>

#include <QImage>

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Object.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/MapManager/MapManager.hpp"


const QPoint AStarPathFinder::directions[] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
const float AStarPathFinder::costs[] = {1.0f, sqrt(2.0f), 1.0f, sqrt(2.0f), 1.0f, sqrt(2.0f), 1.0f, sqrt(2.0f)};
const float AStarPathFinder::sqrtTwo = sqrt(2.0f);


// FIXME possibly risky
inline uint qHash (const QPoint & key)
{
	return qHash(QPair<int, int>{key.x(), key.y()});
}


AStarPathFinder::AStarPathFinder(const MapManager *mapManager): PathFinder{mapManager}
{}


QList< QPointF > AStarPathFinder::getPath(const QPointF &source, const Object *object, const QPointF &target)
{

	QList<QPointF> result;

	const Unit *unit = dynamic_cast<const Unit *>(object);

	if (unit == nullptr) {
		err("Object " + object->getName() +
		" is not of type Unit. PathFinding for non-units is not supported!");
		return result;
	}

	const float objRadius = object->getPrototype()->getProperty(Properties::BaseRadius).toFloat();
	const float gridSize = 2.0f * objRadius;
	QPoint targetPoint = discretizePoint(target, gridSize);
	QPoint sourcePoint = discretizePoint(source, gridSize);
	const Object *targetObject = mapManager->getObjectContaining(undiscretizePoint(targetPoint, gridSize));
	qDebug() << "PF: Starting from: " << sourcePoint << " going to: " << targetPoint <<
			(targetObject != nullptr ? targetObject->getName() : "");


	// Debug
// 	static QSet<QString> names;
// 	if (!names.contains(unit->getName())) {
// 		QSizeF mapSize = mapManager->getMap()->getSize();
// 		QSize discSize = (mapSize / gridSize).toSize();
// 		QImage image{mapSize.toSize(), QImage::Format_ARGB32};
// 		image.fill(Qt::transparent);
// 		QPainter painter{&image};
// 		painter.setBrush(QBrush(Qt::black));
//
// 		for (int x = 0; x < discSize.width(); ++x) {
// 			for (int y = 0; y < discSize.height(); ++y) {
// 				if (!mapManager->canStandOn(unit, undiscretizePoint(QPoint{x, y}, gridSize))) {
// 					painter.drawRect(x * gridSize, y * gridSize, gridSize, gridSize);
// 				}
// 			}
// 		}
//
// 		image.save("/tmp/" + unit->getName() + ".png");
// 		names.insert(unit->getName());
// 	}
	// End of Debug

	QSet<int> visited;
	QHash<QPoint, int> pointToNode;
	std::vector<Node> nodes{10000};
	int lastId = -1;

	struct comp {
		std::vector<Node> *nodes;

		comp(std::vector<Node> *nodes) : nodes{nodes} {}

		inline bool operator()(const int &a, const int& b) {
			return (*nodes)[a].heuristicCost < (*nodes)[b].heuristicCost;
		}
	};

	std::set<int, comp> q{comp{&nodes}};

	pointToNode.insert(sourcePoint, ++lastId);
	const float initialDist = heuristicDistance(sourcePoint, targetPoint, gridSize);
	const float distBound = 11.0f * initialDist;
	nodes[lastId] = Node{sourcePoint, 0.0f, initialDist};
	q.insert(lastId);

	while (!q.empty()) {
		const auto v = *q.begin();
		q.erase(q.begin());

		if (nodes[v].point == targetPoint) {
			qDebug() << "Found path! " << lastId + 1 << "nodes considered";
			appendPathToResult(result, nodes, v, gridSize);
			break;
		}

		const float prevDist = nodes[v].costFromSource;
		visited.insert(v);

		for (int i = 0; i < 8; ++i) {
			QPoint nextPoint = nodes[v].point + directions[i];
			QPointF nextPointReal = undiscretizePoint(nextPoint, gridSize);
			const float nextDist = prevDist + costs[i];

			if (!mapManager->getMap()->isPointValid(nextPointReal) || nextDist > distBound) {
				continue;
			}

			if (!mapManager->canStandOn(unit, nextPointReal)) {
				if (targetObject != nullptr &&
						mapManager->getObjectContaining(nextPointReal) == targetObject) {
					// v is the result - the closest point to the target.
					qDebug() << "Found path! " << lastId + 1 << "nodes considered";
					appendPathToResult(result, nodes, v, gridSize);
					q.clear();
					break;
				}
				continue;
			}

			float nextRank = nextDist + heuristicDistance(nextPoint, targetPoint, gridSize);

			auto iter = pointToNode.find(nextPoint);
			int nextId = -1;
			if (iter != pointToNode.end()) {
				nextId = iter.value();

				if (!visited.contains(nextId)) {
					auto it = q.find(nextId);
					if (it != q.end()) {
						if (nodes[nextId].heuristicCost > nextRank) {
							q.erase(it);
							nodes[nextId].costFromSource = nextDist;
							nodes[nextId].heuristicCost =  nextRank;
							nodes[nextId].previousNode = v;
							q.insert(nextId);
						}

					} else {
						nodes[nextId] = Node{nextPoint, nextDist, nextRank, v};
						q.insert(nextId);
					}
				}
			} else {
				nextId = ++lastId;
				pointToNode.insert(nextPoint, nextId);

				if ((size_t)nextId >= nodes.size()) {
					nodes.resize(nodes.size() * 2);
				}

				nodes[nextId] = Node{nextPoint, nextDist, nextRank, v};
				q.insert(nextId);
			}
		}
	}

	result.append(target);
	return result;
}


QPoint AStarPathFinder::discretizePoint(const QPointF &point, const float gridSize) const
{
	return (point / gridSize).toPoint();
}


QPointF AStarPathFinder::undiscretizePoint(const QPoint &point, const float gridSize) const
{
	QPointF p{point};
	return p * gridSize + QPointF{gridSize / 2.0f, gridSize / 2.0f};
}


float AStarPathFinder::heuristicDistance(const QPoint &from, const QPoint &to, const float gridSize)
{
	QPoint diff = from - to;
	const float side = qMin(abs(diff.x()), abs(diff.y())) / gridSize;
	return diff.manhattanLength() + (sqrtTwo - 2.0f) * side;
}


void AStarPathFinder::appendPathToResult(QList<QPointF> &result,
					 const std::vector<AStarPathFinder::Node> &nodes,
					 int v, const float gridSize) const
{
	QList<int> path;
	while (v != -1 && nodes[v].previousNode != -1) {
		path.append(v);
		v = nodes[v].previousNode;
	}

	while (!path.empty()) {
		result.append(undiscretizePoint(nodes[path.back()].point, gridSize));
		path.pop_back();
	}
}
