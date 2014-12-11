/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Object.hpp"

//TODO use DebugManager instead
#include <QtCore>


Object::Object(const Prototype *prototype)
	: prototype(prototype), parent(nullptr)
{}

Object::~Object()
{}

const Prototype *Object::getPrototype()
{
	return prototype;
}

Object *Object::getParent() const
{
	return parent;
}

void Object::setParent(Object *object)
{
	parent = object;
}

QDataStream &operator<<(QDataStream &out, const Object &object)
{
	//TODO sth, properties, things like that.
	return out;
}

QDataStream &operator>>(QDataStream &in, Object &object)
{
	//TODO same here
	return in;
}
