/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Object.hpp"

//TODO use DebugManager instead
#include <QtCore>

int Object::LastUid = 0;

Object::Object(const Prototype *prototype)
	: prototype{prototype}, uid{++LastUid}, parent{nullptr}, state{BS::State::Idle}, frame{0}
{}


Object::~Object()
{}


const int Object::getUid() const
{
	return uid;
}


const Prototype *Object::getPrototype() const
{
	return prototype;
}


BS::State Object::getState() const
{
	return state;
}


void Object::setState(BS::State state)
{
	this->state = state;
}


int Object::getFrame() const
{
	return frame;
}


void Object::setFrame(int frame)
{
	this->frame = frame;
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
