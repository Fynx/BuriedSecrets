/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QList>
#include <QRectF>
#include <QVector2D>

#include "GameObjects/Object.hpp"


/**
 * @brief The PhysicsEngine class provides implementation independent physics interface.
 */
class PhysicsEngine {
public:
	PhysicsEngine();
	virtual ~PhysicsEngine();

	virtual void addObject(Object *obj, QPointF pos, float angle = 0) = 0;
	virtual void removeObject(Object *obj) = 0;
	virtual void updatePhysics(int msc) = 0;
	virtual void setVelocity(Object *obj, QVector2D v) = 0;
	virtual void setPosition(Object *obj, QPointF pos, float angle = 360.) = 0;
	virtual QPointF getPosition(Object *obj) = 0;
	virtual QList<Object *> testAABB(QRectF rect) = 0;
	virtual QList<Object *> getColliding(Object *obj) = 0;
	virtual Object *getFirstHit(QPointF position, QVector2D direction, float range) = 0;
};
