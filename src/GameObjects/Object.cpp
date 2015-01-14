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

void Object::assignUid()
{
	if (uid == Object::InvalidUid)
		uid = ++LastUid;
}

int Object::getUid() const
{
	if (uid == InvalidUid)
		err("Returning invalid UID!");
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

int Object::getFaction() const
{
	return factionId;
}

void Object::setFaction(int faction)
{
	factionId = faction;
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
	uid = json[Properties::Uid].toInt();
	factionId = json[Properties::Faction].toInt();
	updateUid(uid);
}

QJsonObject Object::saveToJson() const
{
	QJsonObject json;
	json.insert(Properties::Name, getName());
	json.insert(Properties::Type, BS::changeTypeToString(getType()));
	json.insert(Properties::Uid, getUid());
	json.insert(Properties::Faction, getFaction());
	return json;
}

void Object::updateUid(int uid)
{
	LastUid = qMax(LastUid, uid);
}
