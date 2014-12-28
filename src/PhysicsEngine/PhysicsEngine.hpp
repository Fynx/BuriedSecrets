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
	PhysicsEngine() = default;
	virtual ~PhysicsEngine() = default;

	virtual void addObject(Object *obj, const QPointF &pos, const float angle = 0) = 0;
	virtual void removeObject(Object *obj) = 0;
	virtual void updatePhysics(const int msc) = 0;
	virtual void setAngle(Object *obj, float angle) = 0;
	virtual void setVelocity(Object *obj, const QVector2D &v) = 0;
	virtual void setPosition(Object *obj, const QPointF &pos, float angle = 360.0) = 0;
	virtual const QPointF getPosition(const Object *obj) const = 0;
	virtual const float getAngle(const Object *obj) const = 0;
	virtual const QList<const Object *> getObjectsInRect(const QRectF &rect) const = 0;
	virtual const QList<const Object *> getColliding(const Object *obj) const = 0;
	virtual Object *getFirstHit(const QPointF &position, QVector2D direction, const float range) const = 0;
};
