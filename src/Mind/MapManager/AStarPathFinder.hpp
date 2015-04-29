/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QHash>
#include <QPoint>

#include "Mind/MapManager/PathFinder.hpp"

class AccessiblityMap;
class Mind;
class Unit;


class AStarPathFinder : public PathFinder {
public:
	AStarPathFinder(const MapManager *mapManager, const Mind *mind);
	QList<QPointF> getPath(const QPointF &source, const Object *object, const QPointF &target) override;
	void addObject(const Object *object, const QPointF &position) override;
	void removeObject(const Object *object, const QPointF &position) override;

private:
	struct Node {
		Node() : point{-1, -1}, costFromSource{100000.0f}, heuristicCost{100000.0f}, previousNode{-1} {};
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

	AccessiblityMap *getAccessiblityMap(const int gridSize, const Unit *unit);
	float getGridSize(const float radius) const;
	float heuristicDistance(const QPoint& from, const QPoint& to);
	void appendPathToResult(QList<QPointF> &result, const std::vector<Node> &nodes, int v,
				const float gridSize, AccessiblityMap *accMap) const;
	/**
	 * @brief True if the point is close enough to the target to say it is the solution. The target must be in the
	 * target object, otherwise this method will return false.
	 */
	bool isTarget(const QPointF &point, const QPointF &target, const Object *targetObject,
		      const float gridSize) const;

	QHash<int, AccessiblityMap *> accessibilityMaps;
};
