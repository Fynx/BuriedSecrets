/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"
#include "Box2D/Box2D.h"

#include <QList>


class Object;
class Box2DEngine;


class RayCallback : public b2RayCastCallback {
public:
	RayCallback();

private:
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	float nearestFraction;
	Object *obj;

	friend class Box2DEngine;
};

