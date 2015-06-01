/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/MapManager/DiffVisibilityMap.hpp"

#include <cassert>

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Object.hpp"
#include "GameObjects/Unit.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"


bool DiffVisibilityMap::isVisible(const QPointF &point) const
{
	// NOTE This was never needed so it was never implemented.
	err("Not implemented yet.");
	assert(false);
}


void DiffVisibilityMap::update(const VisibilityUpdate &visibilityUpdate)
{
	container.append(visibilityUpdate);
}


void DiffVisibilityMap::clear()
{
	container.clear();
}


bool DiffVisibilityMap::isVisible(const Unit *from, const QPointF &target, const Object *owner,
				  const PhysicsEngine *physicsEngine) const
{
	// There are two approaches possible here:
	//  - use FOV data,
	//  - use raytracing from physics.
	// For now we'll stick to the second one and see how it works.

	QPointF fromPos = physicsEngine->getPosition(from);
	return target == fromPos ? true : physicsEngine->getFirstHit(fromPos,
								     QVector2D{target - fromPos},
								     from->getSightRange()) == owner;
}


VisibilityUpdateDiff DiffVisibilityMap::getCurrentData() const
{
	return container;
}
