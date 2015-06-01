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


/**
 * @brief This is a path finder implementation using A* as the algorithm.
 *
 * The nodes of the search are fake logical tiles of the map obtained by discretizing the coordinates. The grid tiles
 * are squares of side length equal to the diameter of the unit for which the search is done.
 */
class AStarPathFinder: public PathFinder {
public:
	AStarPathFinder(const MapManager *mapManager, const Mind *mind);
	~AStarPathFinder() override;
	QList<QPointF> getPath(const QPointF &source, const Unit *unit, const QPointF &target) override;
	void addObject(const Object *object, const QPointF &position) override;
	void removeObject(const Object *object, const QPointF &position) override;

protected:
	AccessiblityMap *getAccessiblityMap(const int gridSize, const Unit *unit);
	float getGridSize(const float radius) const;
	float heuristicDistance(const QPoint& from, const QPoint& to);
	QPair<bool, QList<QPointF> > tryFindPath(const QPointF &source, const Unit *unit, const float gridSize,
			const QPointF &target, float distanceBound);

private:
	// The search node used by A*.
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

	// Precomputed convenience data.
	static const QPoint directions[8];
	static const float costs[8];
	static const float sqrtTwo;

	/**
	 * @brief True if the point is close enough to the target to say it is the solution. The target must be in the
	 * target object, otherwise this method will return false.
	 */
	bool isTarget(const QPointF &point, const QPointF &target, const Object *targetObject,
			const float gridSize) const;

	QHash<int, AccessiblityMap *> accessibilityMaps;
};
