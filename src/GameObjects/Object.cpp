#include "GameObjects/Object.hpp"

//TODO use DebugManager instead
#include <QtCore>

Object::Object(const Prototype *prototype)
	: prototype(prototype)
{
	qDebug() << "My prototype has a name:" << prototype->getProperty("name").toString();
}

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

