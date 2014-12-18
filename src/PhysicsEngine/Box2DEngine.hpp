/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "PhysicsEngine/PhysicsEngine.hpp"

#include "Box2D/Box2D.h"

#include "PhysicsEngine/ContactListener.hpp"


class Box2DEngine : public PhysicsEngine {
public:
	Box2DEngine();

	void addObject(Object *obj, const QPointF &pos, const float angle = 0) override;
	void removeObject(Object *obj) override;
	void updatePhysics(const int msc) override;
	void setVelocity(Object *obj, const QVector2D &v) override;
	void setPosition(Object *obj, const QPointF &pos, float angle = 360.0) override;
	const QPointF getPosition(const Object *obj) const override;
	const float getAngle(const Object *obj) const override;
	const QList<const Object *> getObjectsInRect(const QRectF &rect) const override;
	const QList<const Object *> getColliding(const Object *obj) const override;
	Object *getFirstHit(const QPointF &position, QVector2D direction, const float range) const override;

private:
	const int32 VELOCITY_ITS = 6;
	const int32 POSITION_ITS = 2;

	b2World world;
	ContactListener listener;
	QMap<const Object *, b2Body *> objects;
};
