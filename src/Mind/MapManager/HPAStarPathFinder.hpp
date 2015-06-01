/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/MapManager/AStarPathFinder.hpp"


/**
 * @brief Hierarchical A* Path Finding.
 *
 * This approach uses A* as a subroutine and therefore depends on A*'s implementation.
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

	// Edge for the abstract graph.
	struct Edge {
		Edge(Node *v, float length, QList<QPointF> realPath) : v{v}, length{length}, realPath{realPath} {}

		HPAStarPathFinder::Node *v;
		float length;
		QList<QPointF> realPath;
	};

	// Node of the abstract graph.
	struct Node {
		QPoint getPoint() const {
			return  segmentBegin + (segmentEnd - segmentBegin) / 2;
		}

		QPoint segmentBegin;
		QPoint segmentEnd;
		std::vector<Edge> edges;
	};

	// A* search node - stored in the queue and used during the path search.
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

	/**
	 * @brief Gets the set of blocks (contatining nodes) for a given gridSize.
	 *
	 * Creates the layer if necessary.
	 */
	BlockNodesContainer *getBlockContainer(const int gridSize, const Unit *unit);
	/**
	 * @brief Creates the layer of blocks including the abstract nodes and edges.
	 */
	BlockNodesContainer *createLayer(const int gridSize, const Unit *unit);
	/**
	 * @brief Translates block coordinates (wrt upper left corner) to an id.
	 */
	const int getBlockIdFromBlockCoords(const int x, const int y, const int gridSize, const Unit *unit);
	/**
	 * @brief Discards and recreates the nodes (along with edges) for the given block in the given blockContainer.
	 */
	void updateBlock(BlockNodesContainer &blockContainer, const QPoint &blockCoords, const int gridSize,
			const Unit *unit);
	/**
	 * @brief Creates nodes inside the given block alond the edge from begin to end.
	 */
	void createNodes(QPoint begin, const QPoint &end, const QPoint &neigbourDirection, Block &block,
			const int gridSize, const Unit *unit);
	/**
	 * @brief Returns the real-world length of the given path.
	 */
	float getPathLength(const QList<QPointF> &path) const;
	/**
	 * @brief Creates intra-edges between blocks and it's neighbour.
	 */
	void connectBlocks(HPAStarPathFinder::BlockNodesContainer &blockContainer, const int neighBlockId,
			HPAStarPathFinder::Node *uNode, AccessiblityMap *accMap);
	/**
	 * @brief Updates all the blocks that need to be recalculated if the given object is added or removed.
	 */
	void updateObject(const Object *object, const QPointF &position);
	/**
	 * @brief Creates, inserts and returns a node in it's block.
	 */
	HPAStarPathFinder::Node *insertNode(const QPointF &position, const int gridSize, const Unit *unit);
	/**
	 * @brief True if the unit can pass from from to to in the given accessiblity map.
	 *
	 * This check is heuristic, but is good enough for our purposes. This method is used to smoothen the paths -
	 * - we can only remove the node B from the path A B C if we can still get from A to C without hitting an
	 * obstacle.
	 */
	bool canPass(const QPointF &from, const Unit *unit, const QPointF &to, AccessiblityMap *accMap);
	/**
	 * @brief Removes all the edges to the node coming from outside.
	 */
	void removeEdges(const Node *node);
	/**
	 * @brief Returns the block id for the given real world position.
	 */
	int getBlockId(const QPointF &position, const int gridSize, const Unit *unit);

	QHash<int, BlockNodesContainer> blockNodes;	// A flat array representing the block matrix.
};
