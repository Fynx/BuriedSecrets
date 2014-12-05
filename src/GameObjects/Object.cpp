/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Object.hpp"

//TODO use DebugManager instead
#include <QtCore>


Object::Object(const Prototype *prototype)
	: prototype{prototype}
{}

Object::~Object()
{}

const Prototype *Object::getPrototype()
{
	return prototype;
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
