/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
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

QString Object::getName() const
{
	return prototype->getProperty(BS::Strings::Properties::Name).toString();
}

BS::State Object::getState() const
{
	return state;
}

void Object::setState(BS::State state)
{
	this->state = state;
	setFrame(0);
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

QVariant &Object::property(const QString &name)
{
	return properties[name];
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
