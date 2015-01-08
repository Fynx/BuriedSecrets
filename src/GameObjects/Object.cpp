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
	return prototype->getProperty(Properties::Name).toString();
}

Object *Object::getParent() const
{
	return parent;
}

void Object::setParent(Object *object)
{
	parent = object;
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

QVariant &Object::property(const QString &name)
{
	return properties[name];
}

int Object::getFrame() const
{
	return frame;
}

void Object::setFrame(int frame)
{
	this->frame = frame;
}

void Object::loadFromJson(const QJsonObject &json)
{
	//TODO
}

QJsonObject Object::saveToJson() const
{
	//TODO
	QJsonObject json;
	json.insert(Properties::Type, BS::changeTypeToString(getType()));
	return json;
}
