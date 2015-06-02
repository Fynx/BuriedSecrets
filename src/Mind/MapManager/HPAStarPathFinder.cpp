/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/MapManager/HPAStarPathFinder.hpp"

#include <set>
#include <stack>
#include <unordered_set>

#include "Common/Strings.hpp"
#include "GameObjects/Object.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/MapManager/AccessibilityMap.hpp"
#include "Mind/MapManager/MapManager.hpp"
#include "Mind/Mind.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"


const int HPAStarPathFinder::AbstractGridSize = 10;


HPAStarPathFinder::HPAStarPathFinder(const MapManager *mapManager, const Mind *mind)
	: AStarPathFinder{mapManager, mind}, mapWidth{mapManager->getMap()->getSize().width()},
	  mapHeight{mapManager->getMap()->getSize().height()}, mind{mind}
{
	auto objects = mind->getAllObjects();
	for (const Object *obj : objects) {
		const Unit *unit = dynamic_cast<const Unit *>(obj);
		if (unit != nullptr && obj->getPrototype()->hasProperty(Properties::BaseRadius)) {
			getBlockContainer(getGridSize(obj->getPrototype()->getProperty(Properties::BaseRadius).toFloat()),
				      unit);
		}
	}
}


HPAStarPathFinder::~HPAStarPathFinder()
{
	for (auto &layer: blockNodes) {
		for (auto &block: layer) {
			for (Node *v: block) {
				delete v;
			}
		}
	}
}


QList<QPointF> HPAStarPathFinder::getPath(const QPointF &source, const Unit *unit, const QPointF &target)
{
	QList<QPointF> path;

	const int gridSize = getGridSize(unit->getPrototype()->getProperty(Properties::BaseRadius).toFloat());
	auto *accMap = AStarPathFinder::getAccessiblityMap(gridSize, unit);
	QPoint discretizedTarget = accMap->discretize(target);
	qDebug() << "HPA*: from " << accMap->discretize(source) << "to" << discretizedTarget;

	if (!accMap->isAccessible(unit, discretizedTarget)) {
		qDebug() << "Target inaccessible";
		path.append(target);
		return path;
	}

	// Step 1: Path from discretized source to all the edges.
	// Step 1.a: Insert source and target into the graph.
	Node *sourceNode = insertNode(source, gridSize, unit);
	Node *targetNode = insertNode(target, gridSize, unit);

	std::vector<SearchNode> nodes(10000);
	std::vector<bool> visited(nodes.size(), false);
	QHash<Node *, int> ptrToId;

	// Step 2: Calculate the path on abstract nodes.
	struct comp {
		comp(std::vector<SearchNode> *nodes) : nodes{nodes} {}

		std::vector<SearchNode> *nodes;

		inline bool operator()(const int &a, const int &b) {
			return (*nodes)[a].heuristicCost < (*nodes)[b].heuristicCost;
		}
	};

	std::set<int, comp> q{comp{&nodes}};
	int lastId = 0;
	ptrToId[sourceNode] = 0;
	nodes[0].node = sourceNode;
	nodes[0].costFromSource = 0.0f;
	nodes[0].heuristicCost = heuristicDistance(sourceNode->getPoint(), discretizedTarget);
	nodes[0].previousNode = -1;
	nodes[0].previousEdge = nullptr;
	visited.push_back(false);
	q.insert(0);
	int v;

	while (!q.empty()) {
		v = *q.begin();
		q.erase(q.begin());
		visited[v] = true;

		if (nodes[v].node == targetNode) {
			// v should be the end of the path.
			// Step 3: Recreate the full path from the result.
			std::stack<int> pathNodes;
			while (v != -1) {
				pathNodes.push(v);
				v = nodes[v].previousNode;
			}

			pathNodes.pop();
			QList<QPointF> tempPath;
			tempPath.append(source);
			while (!pathNodes.empty()) {
				v = pathNodes.top();
				pathNodes.pop();

				const auto &points = nodes[v].previousEdge->realPath;

				for (int i = 0; i < points.size(); ++i) {
					// Check if the point is not doubling.
					if (tempPath.empty() || !BS::Geometry::isZero(
							BS::Geometry::distance(tempPath.back(), points[i]))) {
						tempPath.append(points[i]);
					}
				}
			}

			tempPath.append(target);

			// Step 4: (Optional) Smoothen the path.
			for (int i = 0; i < tempPath.size(); ++i) {	// Skip the first node.
				// Check if the point is unommittable
				if (path.empty() || i >= tempPath.size() - 1 ||
						!canPass(path.back(), unit, tempPath[i + 1], accMap)) {
					path.append(tempPath[i]);
				}
			}

			// Step 5: Remove the source and target... Or not? Yeah, why would we?
			qDebug() << ">>Found path of length" << getPathLength(path) << "searched" << lastId <<
					"meta nodes.\n";

			path.pop_front();
			return path;
		}

		for (Edge &e: nodes[v].node->edges) {
			float nextDist = nodes[v].costFromSource + e.length;
			float nextCost = nextDist + heuristicDistance(e.v->getPoint(), discretizedTarget);
			auto it = ptrToId.find(e.v);
			if (it == ptrToId.end()) {
				++lastId;
				ptrToId.insert(e.v, lastId);
				if (static_cast<int>(visited.size()) <= lastId) {
					visited.resize(visited.size() * 2);
					nodes.resize(nodes.size() * 2);
				}
				nodes[lastId].node = e.v;
				nodes[lastId].costFromSource = nextDist;
				nodes[lastId].heuristicCost = nextCost;
				nodes[lastId].previousNode = v;
				nodes[lastId].previousEdge = &e;
				q.insert(lastId);
			} else {
				int u = it.value();
				if (!visited[u]) {
					auto iter = q.find(u);
					if (iter != q.end()) {
						if (nodes[u].heuristicCost > nextCost) {
							q.erase(iter);
							nodes[u].costFromSource = nextDist;
							nodes[u].heuristicCost = nextCost;
							nodes[u].previousNode = v;
							nodes[u].previousEdge = &e;
							q.insert(u);
						}
					} else {
						nodes[u].node = e.v;
						nodes[u].costFromSource = nextDist;
						nodes[u].heuristicCost = nextCost;
						nodes[u].previousNode = v;
						nodes[u].previousEdge = &e;
						q.insert(u);
					}
				}
			}
		}
	}

	path.append(target);
	return path;
}


void HPAStarPathFinder::addObject(const Object *object, const QPointF &position)
{
	AStarPathFinder::addObject(object, position);
	updateObject(object, position);
}


void HPAStarPathFinder::removeObject(const Object *object, const QPointF &position)
{
	AStarPathFinder::removeObject (object, position);
	updateObject(object, position);
}


HPAStarPathFinder::BlockNodesContainer *HPAStarPathFinder::getBlockContainer(const int gridSize, const Unit *unit)
{
	auto it = blockNodes.find(gridSize);
	if (it == blockNodes.end()) {
		return createLayer(gridSize, unit);
	}

	return &(it.value());
}


HPAStarPathFinder::BlockNodesContainer *HPAStarPathFinder::createLayer(const int gridSize, const Unit *unit)
{
	auto iter = blockNodes.insert(gridSize, BlockNodesContainer{});
	auto &blockContainer = iter.value();

	int blocksPerRow = std::ceil(mapWidth / (1.0f * gridSize) / (1.0f * AbstractGridSize));
	int rows = std::ceil(mapHeight / (1.0f * gridSize) / (1.0f * AbstractGridSize));

	for (int yBegin = 0; yBegin < rows; ++yBegin) {
		for (int xBegin = 0; xBegin < blocksPerRow; ++xBegin) {
			blockContainer.push_back(Block{});
			updateBlock(blockContainer, QPoint{xBegin, yBegin}, gridSize, unit);
		}
	}

	// Debug
//	auto *accMap = AStarPathFinder::getAccessiblityMap(gridSize, unit);
// 	QSizeF mapSize = mapManager->getMap()->getSize();
// 	QImage image{mapSize.toSize(), QImage::Format_ARGB32};
// 	image.fill(Qt::transparent);
// 	QPainter painter{&image};
// 	painter.setPen(QPen(Qt::NoPen));
// 	painter.setBrush(QBrush(Qt::black));
//
// 	for (int x = 0; x < mapWidth; ++x) {
// 		for (int y = 0; y < mapHeight; ++y) {
// 			if (!accMap->isAccessible(unit, QPoint{x, y})) {
// 				painter.drawRect(x * gridSize, y * gridSize, gridSize, gridSize);
// 			}
// 		}
// 	}
//
// 	painter.setBrush(QBrush(Qt::blue));
// 	for (int id = 0; id < (int)blockContainer.size(); ++id) {
// 		for (const Node *node: blockContainer[id]) {
// 			painter.drawRect(QRect(node->segmentBegin * gridSize, node->segmentEnd * gridSize));
// 		}
// 	}
//
// 	painter.end();
// 	image.save("/tmp/" + unit->getName() + ".png");
	// End of Debug

	return &(iter.value());
}


const int HPAStarPathFinder::getBlockIdFromBlockCoords(const int x, const int y, const int gridSize,
						       const Unit *unit)
{
	int blocksPerRow = std::ceil(mapWidth / (1.0f * gridSize) / (1.0f * AbstractGridSize));
	return y * blocksPerRow + x;
}


void HPAStarPathFinder::updateBlock(HPAStarPathFinder::BlockNodesContainer &blockContainer, const QPoint &blockCoords,
				    const int gridSize, const Unit *unit)
{
	const int blockId = getBlockIdFromBlockCoords(blockCoords.x(), blockCoords.y(), gridSize, unit);

// 	qDebug() << ">> Update block" << blockId;
	// Clear the block:
	for (Node *v : blockContainer[blockId]) {
		// Remove v from edges of all blocks.
		removeEdges(v);
	}
	for (Node *v : blockContainer[blockId]) {
		delete v;
		v = nullptr;
	}
	blockContainer[blockId].clear();

	// Create the nodes from segments on the edges.
	QPoint begin = blockCoords * AbstractGridSize; // Discretized coords of the upper left corner.
	// Left edge
	createNodes(begin, QPoint{begin.x(), begin.y() + AbstractGridSize}, QPoint{-1, 0}, blockContainer[blockId],
		    gridSize, unit);

	// Right edge
	createNodes(QPoint{begin.x() + AbstractGridSize - 1, begin.y()},
		    QPoint{begin.x() + AbstractGridSize - 1, begin.y() + AbstractGridSize}, QPoint{1, 0},
		    blockContainer[blockId], gridSize, unit);

	// Top edge
	createNodes(begin, QPoint{begin.x() + AbstractGridSize, begin.y()}, QPoint{0, -1}, blockContainer[blockId],
		    gridSize, unit);

	// Bottom edge
	createNodes(QPoint{begin.x(), begin.y() + AbstractGridSize - 1},
		    QPoint{begin.x() + AbstractGridSize, begin.y() + AbstractGridSize - 1}, QPoint{0, 1},
		    blockContainer[blockId], gridSize, unit);

	// Create intra-edges.
	auto *accMap = getAccessiblityMap(gridSize, unit);
	for (size_t u = 0; u < blockContainer[blockId].size(); ++u) {
		for (size_t v = u + 1; v < blockContainer[blockId].size(); ++v) {
			Node *uNode = blockContainer[blockId][u];
			Node *vNode = blockContainer[blockId][v];
			auto maybePath = AStarPathFinder::tryFindPath(
					accMap->undiscretize(uNode->getPoint()), unit, gridSize,
					accMap->undiscretize(vNode->getPoint()), AbstractGridSize * AbstractGridSize);

			if (maybePath.first == true) {
				float length = getPathLength(maybePath.second);
				uNode->edges.push_back(Edge{vNode, length, maybePath.second});
				std::reverse(std::begin(maybePath.second), std::end(maybePath.second));
				vNode->edges.push_back(Edge{uNode, length, maybePath.second});
			}
		}
	}

	// Create inter-edges.
	int blocksPerRow = std::ceil(mapWidth / (1.0f * gridSize) / (1.0f * AbstractGridSize));
	for (size_t u = 0; u < blockContainer[blockId].size(); ++u) {
		Node *uNode = blockContainer[blockId][u];
		QPoint uPoint = uNode->getPoint();
		if (uPoint.x() == begin.x()) {
			connectBlocks(blockContainer, blockId - 1, uNode, accMap);
		}

		if (uPoint.y() == begin.y()) {
			connectBlocks(blockContainer, blockId - blocksPerRow, uNode, accMap);
		}

		if (uPoint.x() == begin.x() + AbstractGridSize - 1) {
			connectBlocks(blockContainer, blockId + 1, uNode, accMap);
		}

		if (uPoint.y() == begin.y() + AbstractGridSize - 1) {
			connectBlocks(blockContainer, blockId + blocksPerRow, uNode, accMap);
		}
	}
}


void HPAStarPathFinder::createNodes(QPoint begin, const QPoint &end, const QPoint &neighbourDirection,
				    HPAStarPathFinder::Block &block, const int gridSize, const Unit *unit)
{
	auto *accMap = getAccessiblityMap(gridSize, unit);
	QPoint delta = (end - begin) / AbstractGridSize;
	QPoint mirror = begin + neighbourDirection;

	while (begin != end) {
		QPoint previousBegin;
		// Skip inaccessible tiles.
		while(begin != end && (!accMap->isAccessible(unit, begin) || !accMap->isAccessible(unit, mirror))) {
			begin += delta;
			mirror += delta;
		}
		previousBegin = begin;
		// Skip accessible tiles.
		while (begin != end && accMap->isAccessible(unit, begin) && accMap->isAccessible(unit, mirror)) {
			begin += delta;
			mirror += delta;
		}

		if (previousBegin != end) {
			// Create and insert the new node representing a segment on the edge.
			Node *node = new Node{};
			node->segmentBegin = previousBegin;
			node->segmentEnd = begin - delta;
			block.push_back(node);
		}
	}
}


float HPAStarPathFinder::getPathLength(const QList< QPointF > &path) const
{
	float res = 0.0f;
	for (int i = 1; i < path.length(); ++i) {
		res += BS::Geometry::distance(path[i - 1], path[i]);
	}

	return res;
}


void HPAStarPathFinder::connectBlocks(HPAStarPathFinder::BlockNodesContainer &blockContainer, const int neighBlockId,
				      HPAStarPathFinder::Node *uNode, AccessiblityMap *accMap)
{
	if (neighBlockId < 0 || neighBlockId >= static_cast<int>(blockContainer.size())) {
		return;	// Don't worry about this, the right edges will be added anyway.
	}

	QPoint point = uNode->getPoint();
	for (Node *vNode: blockContainer[neighBlockId]) {
		if ((point - vNode->getPoint()).manhattanLength() == 1) {
			QPointF uPoint = accMap->undiscretize(point);
			QPointF vPoint = accMap->undiscretize(vNode->getPoint());
			uNode->edges.push_back(Edge{vNode, 1.0f, {uPoint, vPoint}});
			vNode->edges.push_back(Edge{uNode, 1.0f, {vPoint, uPoint}});
		}
	}
}


void HPAStarPathFinder::updateObject(const Object *object, const QPointF &position)
{
	const Prototype *prot = object->getPrototype();
	if (!prot->hasProperty(Properties::BasePolygon)) {
		return;
	}

	auto polygon = prot->getBasePolygon();
	auto baseCentre = prot->getBaseCentre();

	qreal xMin, xMax, yMin, yMax;
	xMin = xMax = position.x();
	yMin = yMax = position.y();
	for (auto &p: polygon) {
		p += position - baseCentre;
		xMin = qMin(xMin, p.x());
		xMax = qMax(xMax, p.x());
		yMin = qMin(yMin, p.y());
		yMax = qMax(yMax, p.y());
	}

	auto objects = mind->getAllObjects();

	// For each grid size:
	std::unordered_set<int> gridSizes;
	for (const Object *obj : objects) {
		const Unit *unit = dynamic_cast<const Unit *>(obj);
		if (unit != nullptr && obj->getPrototype()->hasProperty(Properties::BaseRadius)) {
			int gridSize = getGridSize(obj->getPrototype()->getProperty(Properties::BaseRadius).toFloat());
			if (gridSizes.find(gridSize) == gridSizes.end()) {
				gridSizes.insert(gridSize);
				auto accMap = getAccessiblityMap(gridSize, unit);
				std::unordered_set<int> updated;
				for (int x = xMin; x <= xMax; ++x) {
					for (int y = yMin; y <= yMax; ++y) {
						QPoint blockCoords = accMap->discretize(QPointF{x * 1.0, y * 1.0});
						blockCoords.setX(blockCoords.x() / AbstractGridSize);
						blockCoords.setY(blockCoords.y() / AbstractGridSize);
						int blockId = getBlockIdFromBlockCoords(
								blockCoords.x(), blockCoords.y(), gridSize, unit);
						qDebug() << blockCoords << x << y;
						if (updated.find(blockId) == updated.end()) {
							updated.insert(blockId);
							updateBlock(blockNodes[gridSize], blockCoords, gridSize, unit);

							// Debug
// 							QSizeF mapSize = mapManager->getMap()->getSize();
// 							QImage image{mapSize.toSize(), QImage::Format_ARGB32};
// 							image.fill(Qt::transparent);
// 							QPainter painter{&image};
// 							painter.setPen(QPen(Qt::NoPen));
// 							painter.setBrush(QBrush(Qt::black));
//
// 							for (int x = 0; x < mapWidth; ++x) {
// 								for (int y = 0; y < mapHeight; ++y) {
// 									if (!accMap->isAccessible(unit, QPoint{x, y})) {
// 										painter.drawRect(x * gridSize,
// 												 y * gridSize,
// 												 gridSize, gridSize);
// 									}
// 								}
// 							}
//
// 							painter.setBrush(QBrush(Qt::blue));
// 							for (int id = 0; id < (int)blockNodes[gridSize].size(); ++id) {
// 								for (const Node *node: blockNodes[gridSize][id]) {
// 									painter.drawRect(QRect(node->segmentBegin *
// 													gridSize,
// 											       node->segmentEnd *
// 													gridSize));
// 								}
// 							}
//
// 							painter.end();
// 							image.save("/tmp/" + unit->getName() + ".png");
							// End of debug
						}
					}
				}
			}
		}
	}
}


HPAStarPathFinder::Node *HPAStarPathFinder::insertNode(const QPointF &position, const int gridSize, const Unit *unit)
{
	auto accMap = getAccessiblityMap(gridSize, unit);
	QPoint positionDiscretized = accMap->discretize(position);
	int blockId = getBlockId(position, gridSize, unit);
	auto &blockContainer = blockNodes[gridSize];
	for (Node *v: blockContainer[blockId]) {
		if (v->getPoint() == positionDiscretized) {
			return v;	// No need to reinsert.
		}
	}

	Node *v = new Node{};
	v->segmentBegin = positionDiscretized;
	v->segmentEnd = positionDiscretized;

	for (Node *u: blockContainer[blockId]) {
		auto maybePath = AStarPathFinder::tryFindPath(
				accMap->undiscretize(u->getPoint()), unit, gridSize,
				accMap->undiscretize(v->getPoint()), AbstractGridSize * AbstractGridSize);

		if (maybePath.first == true) {
			float length = getPathLength(maybePath.second);
			u->edges.push_back(Edge{v, length, maybePath.second});
			std::reverse(std::begin(maybePath.second), std::end(maybePath.second));
			v->edges.push_back(Edge{u, length, maybePath.second});
		}
	}

	blockContainer[blockId].push_back(v);
	return v;
}


bool HPAStarPathFinder::canPass(const QPointF &from, const Unit *unit, const QPointF &to, AccessiblityMap *accMap)
{
	QPointF fromDisc = accMap->discretize(from);
	QPointF toDisc = accMap->discretize(to);
	QPointF delta = toDisc - fromDisc;
	float length = sqrt(delta.x() * delta.x() + delta.y() * delta.y());
	delta /= length;
	int intLength = length;

	QPointF p = fromDisc;
	for (int i = 0; i <= intLength; ++i, p += delta) {
		if (!accMap->isAccessible(unit, p.toPoint())) {
			return false;
		}
	}

	return true;
}


void HPAStarPathFinder::removeEdges (const HPAStarPathFinder::Node *node)
{
	for (const Edge &e : node->edges) {
		// Remove edges as quickly as possible (O(1)).
		for (std::size_t i = 0; i < e.v->edges.size(); ++i) {
			if (e.v->edges[i].v == node) {
				std::swap(e.v->edges[i], e.v->edges.back());
				e.v->edges.pop_back();
				--i;
			}
		}
	}
}


int HPAStarPathFinder::getBlockId(const QPointF &position, const int gridSize, const Unit *unit)
{
	auto accMap = getAccessiblityMap(gridSize, unit);
	QPoint positionDiscretized = accMap->discretize(position);
	QPoint blockCoords{positionDiscretized.x() / AbstractGridSize, positionDiscretized.y() / AbstractGridSize};
	return getBlockIdFromBlockCoords(blockCoords.x(), blockCoords.y(), gridSize, unit);
}

