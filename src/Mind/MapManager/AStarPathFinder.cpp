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

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Object.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/MapManager/MapManager.hpp"
#include "Mind/MapManager/PrecomputedAccessibilityMap.hpp"
#include "Mind/Mind.hpp"


const QPoint AStarPathFinder::directions[] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
const float AStarPathFinder::costs[] = {1.0f, sqrt(2.0f), 1.0f, sqrt(2.0f), 1.0f, sqrt(2.0f), 1.0f, sqrt(2.0f)};
const float AStarPathFinder::sqrtTwo = sqrt(2.0f);


inline uint qHash (const QPoint & key)
{
	return qHash(QPair<int, int>{key.x(), key.y()});
}


AStarPathFinder::AStarPathFinder(const MapManager *mapManager, const Mind *mind)
		: PathFinder{mapManager}
{
	auto objects = mind->getAllObjects();
	for (const Object *obj : objects) {
		const Unit *unit = dynamic_cast<const Unit *>(obj);
		if (unit != nullptr && obj->getPrototype()->hasProperty(Properties::BaseRadius)) {
			getAccessiblityMap(getGridSize(
					obj->getPrototype()->getProperty(Properties::BaseRadius).toFloat()), unit);
		}
	}
}


QList< QPointF > AStarPathFinder::getPath(const QPointF &source, const Object *object, const QPointF &target)
{
	QList<QPointF> result;

	const Unit *unit = dynamic_cast<const Unit *>(object);

	if (unit == nullptr) {
		err("Object " + object->getName() +
		" is not of type Unit. PathFinding for non-units is not supported!");
		return result;
	}

	const float gridSize = getGridSize(object->getPrototype()->getProperty(Properties::BaseRadius).toFloat());
	auto *accMap = getAccessiblityMap(gridSize, unit);
	QPoint targetDiscrete = accMap->discretize(target);
	QPoint sourceDiscrete = accMap->discretize(source);
	const Object *targetObject =
		mapManager->getObjectContaining(accMap->undiscretize(targetDiscrete),
		                                gridSize / 2.0f);
// 	qDebug() << "PF: Starting from: " << sourceDiscrete << " going to: " << targetDiscrete
// 		<< (targetObject != nullptr ? targetObject->getName() : "no object");

	QHash<QPoint, int> pointToNode;
	std::vector<bool> visited(10000, false);
	std::vector<Node> nodes(10000);
	int lastId = -1;

	struct comp {
		std::vector<Node> *nodes;

		comp(std::vector<Node> *nodes) : nodes{nodes} {}

		inline bool operator()(const int &a, const int& b) {
			return (*nodes)[a].heuristicCost < (*nodes)[b].heuristicCost;
		}
	};

	std::set<int, comp> q{comp{&nodes}};

	pointToNode.insert(sourceDiscrete, ++lastId);
	const float initialDist = heuristicDistance(sourceDiscrete, targetDiscrete);
	float distBound = 6.0f * initialDist;
	nodes[lastId] = Node{sourceDiscrete, 0.0f, initialDist};
	q.insert(lastId);

	while (!q.empty()) {
		const auto v = *q.begin();
		q.erase(q.begin());

		if (nodes[v].heuristicCost > distBound) {
			continue;	// We might have put the node in the queue before getting an improved distBound,
					// so we need to check here if we want to spend any work on this node.
		}

		if (nodes[v].point == targetDiscrete ||
				isTarget(accMap->undiscretize(nodes[v].point), target, targetObject, gridSize)) {
// 			qDebug() << "Found path!";
			appendPathToResult(result, nodes, v, gridSize, accMap);
			break;
		}

		const float prevDist = nodes[v].costFromSource;
		visited[v] = true;

		for (int i = 0; i < 8; ++i) {
			QPoint nextPoint = nodes[v].point + directions[i];
			QPointF nextPointReal = accMap->undiscretize(nextPoint);
			const float nextDist = prevDist + costs[i];

			if (!mapManager->getMap()->isPointValid(nextPointReal) || nextDist > distBound) {
				continue;
			}

			if (nextPoint == targetDiscrete && nextDist < distBound) {
				distBound = nextDist;	// We can definetely find a solution closer!
			}

			float nextRank = nextDist + heuristicDistance(nextPoint, targetDiscrete);

			if (!accMap->isAccessible(unit, nextPoint)) {
				if (isTarget(nextPointReal, target, targetObject, gridSize)) {
					nextRank = nextDist;	// We will be at the end, so we assume the heuristic
								// distance to be 0.
					distBound = qMin(distBound, nextDist);
				} else {
					continue;	// Not accessible and not the target.
				}
			}

			auto iter = pointToNode.find(nextPoint);
			int nextId = -1;
			if (iter != pointToNode.end()) {
				nextId = iter.value();

				if (static_cast<int>(visited.size()) <= nextId) {
					visited.resize(2 * visited.size(), false);
				}

				if (!visited[nextId]) {
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

// 	qDebug() << lastId + 1 << "nodes considered";
	while (result.length() >= 2 &&
			BS::Geometry::distance(target, result.at(result.length() - 2)) < gridSize * sqrtTwo) {
		result.pop_back();
	}
	result.append(target);
	return result;
}


void AStarPathFinder::addObject (const Object *object, const QPointF &position)
{
	for (auto *accMap : accessibilityMaps.values()) {
		accMap->addObject(object, position);
	}
}


void AStarPathFinder::removeObject (const Object *object, const QPointF &position)
{
	for (auto *accMap : accessibilityMaps.values()) {
		accMap->removeObject(object, position);
	}
}


AccessiblityMap *AStarPathFinder::getAccessiblityMap(const int gridSize, const Unit *unit)
{
	const auto it = accessibilityMaps.find(gridSize);
	if (it != accessibilityMaps.end()) {
		return it.value();
	}

	AccessiblityMap *map = new PrecomputedAccessibilityMap(mapManager, gridSize, unit);
	accessibilityMaps.insert(gridSize, map);
	return map;
}


float AStarPathFinder::getGridSize(const float radius) const
{
	return 2.0f * radius;
}


float AStarPathFinder::heuristicDistance(const QPoint &from, const QPoint &to)
{
	return BS::Geometry::distance(from, to);
}


void AStarPathFinder::appendPathToResult(QList<QPointF> &result, const std::vector<AStarPathFinder::Node> &nodes, int v,
					 const float gridSize, AccessiblityMap *accMap) const
{
	QList<int> path;
	while (v != -1 && nodes[v].previousNode != -1) {
		path.append(v);
		v = nodes[v].previousNode;
	}

	while (!path.empty()) {
		result.append(accMap->undiscretize(nodes[path.back()].point));
		path.pop_back();
	}
}


bool AStarPathFinder::isTarget(const QPointF& point, const QPointF& target, const Object* targetObject,
			       const float gridSize) const
{
	return targetObject != nullptr && BS::Geometry::distance(point, target) <= gridSize * sqrtTwo &&
			mapManager->getObjectContaining(point, gridSize / 2.0f) == targetObject;
}

