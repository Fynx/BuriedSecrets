/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QPoint>

#include "Mind/MapManager/PathFinder.hpp"


class AStarPathFinder : public PathFinder {
public:
	AStarPathFinder(const MapManager *mapManager);
	QList<QPointF> getPath(const QPointF &source, const Object *object, const QPointF &target) override;

private:
	struct Node {
		Node() : point{-1, -1}, costFromSource{10000.0f}, heuristicCost{100000.0f}, previousNode{-1} {};
		Node(const QPoint &point, const float costFromSource, const float heuristicCost,
		     const int previousNode = -1)
			: point{point}, costFromSource{costFromSource}, heuristicCost{heuristicCost},
			  previousNode{previousNode} {}

		QPoint point;
		float costFromSource;
		float heuristicCost;
		int previousNode;
	};

	static const QPoint directions[8];
	static const float costs[8];
	static const float sqrtTwo;

	/**
	 * @brief This method returns the discretized point. It chooses the closest point available out
	 *
	 * @param point ...
	 * @param gridSize ...
	 * @return QPoint
	 */
	QPoint discretizePoint(const QPointF &point, const float gridSize) const;
	QPointF undiscretizePoint(const QPoint &point, const float gridSize) const;
	float heuristicDistance(const QPoint &from, const QPoint &to, const float gridSize);
	void appendPathToResult(QList<QPointF> &result, const std::vector<Node> &nodes, int v,
				const float gridSize) const;
};