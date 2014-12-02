/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "PhysicsEngine.hpp"

#include "Box2D/Box2D.h"

class Box2DEngine : public PhysicsEngine {
public:
	Box2DEngine();

	void addObject(Object *obj, QPointF pos);
	void removeObject(Object *obj);
	void updatePhysics(int msc);
	void setVelocity(Object *obj, QVector2D v);
	void setPosition(Object *obj, QPointF pos);
	QPointF getPosition(Object *obj);
	QList<Object *> testAABB(QRectF rect);
	QList<Object *> getColliding(Object *obj);
	Object *getFirstHit(QPointF position, QVector2D direction);

private:
	b2World world;
};
