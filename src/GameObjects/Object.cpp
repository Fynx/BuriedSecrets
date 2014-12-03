/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Object.hpp"

//TODO use DebugManager instead
#include <QtCore>


Object::Object(const Prototype *prototype)
	: prototype(prototype)
{}

Object::~Object()
{}

const Prototype *Object::getPrototype()
{
	return prototype;
}

const QPointF &Object::getPosition() const
{
	return position;
}

void Object::setPosition(const float x, const float y)
{
	position.setX(x);
	position.setY(y);
}

QDataStream &operator<<(QDataStream &out, const Object &object)
{
	out << object.position;
	qDebug() << "\t" << object.position;
	//TODO sth, properties, things like that.
	return out;
}

QDataStream &operator>>(QDataStream &in, Object &object)
{
	in >> object.position;
	qDebug() << "\t" << object.position;
	//TODO same here
	return in;
}
