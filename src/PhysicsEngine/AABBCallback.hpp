/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"
#include "Box2D/Box2D.h"

#include <QList>


class Object;
class Box2DEngine;

// Should be used just once. New callback for every query
class AABBCallback : public b2QueryCallback {
public:
	AABBCallback();

private:
	bool ReportFixture(b2Fixture* fixture);
	QList<Object*> foundObjects;

	friend class Box2DEngine;
};

