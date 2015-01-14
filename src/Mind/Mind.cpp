﻿/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Mind.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Building.hpp"
#include "GameObjects/Camp.hpp"
#include "GameObjects/Equipment.hpp"
#include "GameObjects/Fortification.hpp"
#include "GameObjects/Mob.hpp"
#include "GameObjects/Unit.hpp"

const int Mind::PlayerFactionId = 1;

Mind::Mind(DataManager *dataManager, PhysicsEngine *physicsEngine, SoundsManager *soundsManager)
	: dataManager(dataManager),
	  physics(physicsEngine),
	  soundsManager(soundsManager),
	  animatorManager(new AnimatorManager(this)),
	  mapManager(nullptr),
	  constructor(new ItemConstructor(dataManager, this))
{
	info("Mind initialized");
	soundsManager->onEvent(QString("test: success"));
}

Mind::~Mind()
{
	delete animatorManager;
	delete mapManager;
	qDeleteAll(objects);
}

Object *Mind::getObjectFromUid(const int uid)
{
	if (uidToObject.contains(uid))
		return uidToObject[uid];
	else
		warn("Mind::getObjectFromUid: uid not found");
	return nullptr;
}

PhysicsEngine *Mind::physicsEngine()
{
	return physics;
}

ItemConstructor *Mind::itemConstructor()
{
	return constructor;
}

void Mind::loadFromJson(const QJsonObject &json)
{
	delete mapManager;
	mapManager = new MapManager(json);

	const QJsonArray &objs = json[Properties::Objects].toArray();

	QSet<QPair<Object *, QPair<double, double> > > objectsToAdd;

	for (const QJsonValue &val : objs) {
		const QJsonObject &obj = val.toObject();
		if (!obj.contains(Properties::Name)) {
			err("Object without a name! Skipping.");
			continue;
		}
		qDebug() << "\tload" << obj[Properties::Name].toString();
		Object *object = createObjectFromJson(obj[Properties::Name].toString(), obj);

		for (const QJsonValue &value : obj[Properties::Animators].toArray())
			if (!animatorManager->addObject(value.toString(), object))
				qDebug() << "\t\tfailed to add to animator" << value.toString();

		// Pair because stupid qt
		QPair<double, double> coordinates = {obj[Properties::X].toDouble(), obj[Properties::Y].toDouble()};
		objectsToAdd.insert(qMakePair(object, coordinates));
	}

	for (auto &p : objectsToAdd) {
		p.first->assignUid();
		addObject(p.first, QPointF(p.second.first, p.second.second));
	}

	//TODO assign pointers in Objects, you can put uid assigning before this for loop here for safety.
}

QJsonObject Mind::saveToJson() const
{
	QJsonObject json;
	QJsonArray objs;

	json.insert(Properties::MapName, mapManager->getMap()->getName());
	json.insert(Properties::MapDesc, mapManager->getMap()->getDesc());

	for (Object *obj : objects) {
		qDebug() << "\tsave" << obj->getName();
		QJsonObject objJson = obj->saveToJson();

		QVector<QString> animators = animatorManager->getAnimatorsForObject(obj);
		objJson.insert(Properties::Animators, QJsonArray::fromStringList(animators.toList()));

		QPointF pos = physics->getPosition(obj);
		objJson.insert(Properties::X, pos.x());
		objJson.insert(Properties::Y, pos.y());

		objs.append(objJson);
	}
	json.insert(Properties::Objects, objs);

	return json;
}

const Map *Mind::getMap() const
{
	return mapManager->getMap();
}

const MapManager *Mind::getMapManager() const
{
	return mapManager;
}

void Mind::addObject(Object *object, const QPointF &position)
{
	addObject(object);
	physics->addObject(object, position);
}

void Mind::addObject(Object *object)
{
	objects.append(object);
	uidToObject[object->getUid()] = object;
}

void Mind::removeObject(Object *object)
{
	qDebug() << "removeObject:" << object->getUid();
	animatorManager->removeObject(object);
	objects.removeAll(object);
	uidToObject.remove(object->getUid());
	physics->removeObject(object);
}

Faction *Mind::getFactionById(int id)
{
	if (!factions.contains(id))
		qDebug() << "No such Faction! " << id;
	return factions.value(id);
}

const Faction *Mind::getFactionById(int id) const
{
	if (!factions.contains(id))
		qDebug() << "No such Faction! " << id;
	return factions.value(id);
}

Faction *Mind::getPlayerFaction()
{
	return getFactionById(PlayerFactionId);
}

const Faction *Mind::getPlayerFaction() const
{
	return getFactionById(PlayerFactionId);
}

Object *Mind::createObject(BS::Type type, const QString &name)
{
	Object *obj;
	switch (type) {
		case BS::Type::Invalid: {
			qDebug() << "Explosion: Invalid object type";
			break;
		}
		case BS::Type::Building: {
			Building *building = new Building(dataManager->getPrototype(name));
			obj = building;
			break;
		}
		case BS::Type::Camp: {
			Camp *camp = new Camp(dataManager->getPrototype(name));
			obj = camp;
			break;
		}
		case BS::Type::Equipment: {
			Equipment *equipment = new Equipment(dataManager->getPrototype(name));
			obj = equipment;
			break;
		}
		case BS::Type::Faction: {
			Faction *faction = new Faction(dataManager->getPrototype(name));
			factions.insert(faction->getFactionId(), faction);
			obj = faction;
			break;
		}
		case BS::Type::Fortification: {
			Fortification *fortification = new Fortification(dataManager->getPrototype(name));
			obj = fortification;
			break;
		}
		case BS::Type::Mob: {
			Mob *mob = new Mob(dataManager->getPrototype(name));
			obj = mob;
			break;
		}
		case BS::Type::Unit: {
			Unit *unit = new Unit(dataManager->getPrototype(name));
			obj = unit;

			// ----- Cut here ----- //
			QList<QPointF> tmpPath;
			tmpPath.append(QPointF(50, 5));
			tmpPath.append(QPointF(5, 50));
			tmpPath.append(QPointF(5, 10));
			tmpPath.append(QPointF(30, 50));
			tmpPath.append(QPointF(50, 25));
			tmpPath.append(QPointF(5, 5));
			unit->setCurrentPath(tmpPath);
			// ----- Cut here ----- //

			break;
		}
		default: {
			qDebug() << "blablabla...\n" << "blabla?";
		}
	}

	return obj;
}

Object *Mind::createObjectFromJson(const QString &name, const QJsonObject &json)
{
	BS::Type type = BS::changeStringToType(json[Properties::Type].toString());
	Object *obj = createObject(type, name);
	obj->loadFromJson(json);

	return obj;
}
