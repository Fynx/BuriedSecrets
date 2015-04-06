/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Object.hpp"

int Object::LastUid = Object::InvalidUid;

Object::Object(const Prototype *prototype)
	: prototype(prototype), uid(InvalidUid), state(BS::State::Idle), frame(0)
{}

Object::~Object()
{}

int Object::assignUid()
{
	if (uid == Object::InvalidUid)
		uid = ++LastUid;
	return uid;
}

int Object::getUid() const
{
	if (uid == InvalidUid)
		err("Returning invalid UID!");
	return uid;
}

/** If the object is removable, it will not be saved to file */
bool Object::isRemovable() const
{
	return false;
}

const Prototype *Object::getPrototype() const
{
	return prototype;
}

QString Object::getName() const
{
	if (prototype == nullptr)
		return BS::changeTypeToString(getType());
	return prototype->getProperty(Properties::Name).toString();
}

int Object::getFactionId() const
{
	return factionId;
}

void Object::setFactionId(const int factionId)
{
	this->factionId = factionId;
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

const QVariant Object::property(const QString &name) const
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
	uid = json[Attributes::Uid].toInt();
	factionId = json[Attributes::Faction].toInt();
	updateUid(uid);
}

QJsonObject Object::saveToJson() const
{
	QJsonObject json;
	json[Properties::Name] = getName();
	json[Attributes::Uid] = getUid();
	json[Attributes::Faction] = getFactionId();
	return json;
}

void Object::updateUid(int uid)
{
	LastUid = qMax(LastUid, uid);
}
