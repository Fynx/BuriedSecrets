/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "PhysicsEngine.hpp"
#include "ContactListener.hpp"

#include "Box2D/Box2D.h"

class Box2DEngine : public PhysicsEngine {
public:
	Box2DEngine();

	void addObject(Object *obj, QPointF pos, float angle = 0);
	void removeObject(Object *obj);
	void updatePhysics(int msc);
	void setVelocity(Object *obj, QVector2D v);
	void setPosition(Object *obj, QPointF pos, float angle = 360.);
	QPointF getPosition(Object *obj);
	QList<Object *> testAABB(QRectF rect);
	QList<Object *> getColliding(Object *obj);
	Object *getFirstHit(QPointF position, QVector2D direction);

private:
	const int32 VELOCITY_ITS = 6;
	const int32 POSITION_ITS = 2;

	b2World world;
	ContactListener listener;
	QMap<Object *, b2Body*> objects;
};
