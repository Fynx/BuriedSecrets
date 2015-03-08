/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/MapManager/VisibilityMap.hpp"
#include "Mind/MapManager/VisibilityUpdate.hpp"


class DiffVisibilityMap : public VisibilityMap {
public:
	bool isVisible(const QPointF &point) const override;
	void update(const VisibilityUpdate &visibilityUpdate) override;
	void clear() override;

protected:
	bool isVisible(const Unit *from, const QPointF &target, const Object *owner,
		       const PhysicsEngine *physicsEngine) const override;

private:
	VisibilityUpdateDiff container;
};