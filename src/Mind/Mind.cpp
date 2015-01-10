/* YoLoDevelopment, 2014
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

Mind::Mind(DataManager *dataManager, PhysicsEngine *physicsEngine, SoundsManager *soundsManager)
	: dataManager(dataManager),
	  physics(physicsEngine),
	  soundsManager(soundsManager),
	  animatorManager(new AnimatorManager(this)),
	  mapManager(nullptr)
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

void Mind::loadFromJson(const QJsonObject &json)
{
	delete mapManager;
	mapManager = new MapManager(json);

	const QJsonObject &objs = json[Properties::Objects].toObject();

	for (const QString &key : objs.keys()) {
		qDebug() << key;
		const QJsonObject &obj = objs[key].toObject();
		Object *object = createObjectFromJson(key, obj);

		for (const QJsonValue &value : obj[Properties::Animators].toArray())
			if (!animatorManager->addObject(value.toString(), object))
				qDebug() << "\t\tfailed to add to animator" << value.toString();

		QPointF coordinates = {obj[Properties::X].toDouble(), obj[Properties::Y].toDouble()};
		addObject(object, coordinates);
	}
}

QJsonObject Mind::saveToJson() const
{
	QJsonObject json;
	QJsonObject objs;

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

		objs.insert(obj->getName(), objJson);
	}
	json.insert(Properties::Objects, objs);

	return json;
}

const Map *Mind::getMap() const
{
	return mapManager->getMap();
}

void Mind::addObject(Object *object, const QPointF &position)
{
	objects.append(object);
	uidToObject[object->getUid()] = object;
	physics->addObject(object, position);
}

void Mind::removeObject(Object *object)
{
	qDebug() << "removeObject:" << object->getUid();
	animatorManager->removeObject(object);
	objects.removeAll(object);
	uidToObject.remove(object->getUid());
	physics->removeObject(object);
}

Faction *Mind::getFactionFromUid(int uid)
{
	if (!factions.contains(uid))
		qDebug() << "No such Faction! " << uid;
	return factions.value(uid);
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
