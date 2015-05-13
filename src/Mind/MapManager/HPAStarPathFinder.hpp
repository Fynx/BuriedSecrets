/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/MapManager/AStarPathFinder.hpp"


/**
 * @brief Hierarchical A* Path Finding.
 */
class HPAStarPathFinder: public AStarPathFinder {
public:
	HPAStarPathFinder(const MapManager *mapManager, const Mind *mind);
	~HPAStarPathFinder() override;
	QList<QPointF> getPath(const QPointF &source, const Unit *unit, const QPointF &target) override;
	void addObject(const Object *object, const QPointF &position) override;
	void removeObject(const Object *object, const QPointF &position) override;

private:
	static const int AbstractGridSize;
	const qreal mapWidth, mapHeight;
	const Mind *mind;

	struct Node;

	struct Edge {
		Edge(Node *v, float length, QList<QPointF> realPath) : v{v}, length{length}, realPath{realPath} {}

		HPAStarPathFinder::Node *v;
		float length;
		QList<QPointF> realPath;
	};

	struct Node {
		QPoint getPoint() const {
			return  segmentBegin + (segmentEnd - segmentBegin) / 2;
		}

		QPoint segmentBegin;
		QPoint segmentEnd;
		std::vector<Edge> edges;
	};

	struct SearchNode {
		SearchNode() : costFromSource{100000.0f}, heuristicCost{100000.0f} {}

		Node *node;
		float costFromSource;
		float heuristicCost;
		int previousNode;
		Edge *previousEdge;
	};

	typedef std::vector<Node *> Block;
	typedef std::vector<Block> BlockNodesContainer;

	BlockNodesContainer *getBlockNodes(const int gridSize, const Unit *unit);
	BlockNodesContainer *createLayer(const int gridSize, const Unit *unit);
	const int getBlockIdFromBlockCoords(const int x, const int y, const int gridSize, const Unit *unit);
	void updateBlock(BlockNodesContainer &blockContainer, const QPoint &blockCoords, const int gridSize,
			 const Unit *unit);
	void createNodes(QPoint begin, const QPoint &end, const QPoint &neigbourDirection, Block &block,
			 const int gridSize, const Unit *unit);
	float getPathLength(const QList<QPointF> &path) const;
	void connectBlocks(HPAStarPathFinder::BlockNodesContainer &blockContainer, const int neighBlockId,
			   HPAStarPathFinder::Node *uNode, AccessiblityMap *accMap);
	void updateObject(const Object *object, const QPointF &position);
	HPAStarPathFinder::Node *insertNode(const QPointF &position, const int gridSize, const Unit *unit);
	bool canPass(const QPointF &from, const Unit *unit, const QPointF &to, AccessiblityMap *accMap);

	QHash<int, BlockNodesContainer> blockNodes;	// A flat array representing the block matrix.
};
