/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"
#include "Box2D/Box2D.h"

#include <QMap>


class Object;
class Box2DEngine;


class ContactListener : public b2ContactListener {
public:
	ContactListener();

private:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	QMap<const Object *, QSet<const Object *> > collisions;

	friend class Box2DEngine;
};
