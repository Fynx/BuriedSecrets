/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Mind.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Equipment.hpp"
#include "GameObjects/Location.hpp"
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
	mapManager = new MapManager(json, physics, PlayerFactionId);

	const QJsonArray &objs = json[Data::Objects].toArray();

	QSet<QPair<Object *, QPair<double, double> > > objectsToAdd;

	for (const QJsonValue &val : objs) {
		const QJsonObject &obj = val.toObject();
		if (!obj.contains(Properties::Name)) {
			err("Object without a name! Skipping.");
			continue;
		}
		qDebug() << "\tload" << obj[Properties::Name].toString() << obj[Attributes::Uid].toInt();
		Object *object = createObjectFromJson(obj[Properties::Name].toString(), obj);

		for (const QJsonValue &value : obj[Data::Animators].toArray())
			if (!animatorManager->addObject(value.toString(), object))
				qDebug() << "\t\tfailed to add to animator" << value.toString();

		// Pair because stupid qt
		QPair<double, double> coordinates = {obj[TempData::X].toDouble(), obj[TempData::Y].toDouble()};
		objectsToAdd.insert(qMakePair(object, coordinates));
	}

	for (auto &p : objectsToAdd) {
		p.first->assignUid();
		if (p.second.first != 0.0 || p.second.second != 0.0)
			addObject(p.first, QPointF(p.second.first, p.second.second));
		else
			addObject(p.first);
	}

	/** Set pointers */

	//WARNING ItemConstructor is NOT used. Because what for.

	info("Binding objects...");

	int objectsSize = objects.size();
	for (int i = 0; i < objectsSize; ++i) {
		Object *object = objects[i];
		qDebug() << "\t" << object->getName();
		if (object->getType() == BS::Type::Faction) {
			Faction *faction = dynamic_cast<Faction *>(object);

			factions.insert(object->getFactionId(), faction);
			for (int objectUid : faction->getUnitsUids())
				getObjectFromUid(objectUid)->setFactionId(object->getFactionId());

			int eqUid = faction->getEquipmentUid();
			if (eqUid == Object::InvalidUid) {
				Object *eq = createObject(BS::Type::Equipment, "equipment");
				eqUid = eq->assignUid();
				addObject(eq);
			}
			Object *eq = getObjectFromUid(eqUid);
			Q_ASSERT(eq->getType() == BS::Type::Equipment);
			faction->setEquipment(dynamic_cast<Equipment *>(eq));
		} else if (object->getType() == BS::Type::Unit) {
			Unit *unit = dynamic_cast<Unit *>(object);

			int eqUid = unit->getEquipmentUid();
			if (eqUid == Object::InvalidUid) {
				Object *eq = createObject(BS::Type::Equipment, "equipment");
				eqUid = eq->assignUid();
				addObject(eq);
			}
			Object *eq = getObjectFromUid(eqUid);
			Q_ASSERT(eq->getType() == BS::Type::Equipment);
			unit->setEquipment(dynamic_cast<Equipment *>(eq));
		} else if (object->getType() == BS::Type::Equipment) {
			Equipment *eq = dynamic_cast<Equipment *>(object);

			for (int itemUid : eq->getItemsUids())
				eq->addItem(dynamic_cast<Item *>(getObjectFromUid(itemUid)));
			for (BS::Slot slot : BS::getSlots())
				if (eq->getSlotItemUid(slot) != Object::InvalidUid)
					eq->putItemIntoSlot(slot, dynamic_cast<Item *>(getObjectFromUid(eq->getSlotItemUid(slot))));
		}
	}

	info("done.");
}

QJsonObject Mind::saveToJson() const
{
	QJsonObject json;
	QJsonArray objs;

	json.insert(MapProperties::MapName, mapManager->getMap()->getName());
	json.insert(MapProperties::MapDesc, mapManager->getMap()->getDesc());

	for (Object *obj : objects) {
		if (obj->isRemovable())
			continue;
		qDebug() << "\tsave" << obj->getName();
		QJsonObject objJson = obj->saveToJson();

		QVector<QString> animators = animatorManager->getAnimatorsForObject(obj);
		objJson.insert(Data::Animators, QJsonArray::fromStringList(animators.toList()));

		QPointF pos = physics->getPosition(obj);
		objJson.insert(TempData::X, pos.x());
		objJson.insert(TempData::Y, pos.y());

		objs.append(objJson);
	}
	json.insert(Data::Objects, objs);

	return json;
}

const Map *Mind::getMap() const
{
	return mapManager->getMap();
}

MapManager *Mind::getMapManager() const
{
	return mapManager;
}

void Mind::pauseGame()
{
	animatorManager->pauseGame();
}

void Mind::resumeGame()
{
	animatorManager->resumeGame();
}

void Mind::addObject(Object *object, const QPointF &position)
{
	addObject(object);
	physics->addObject(object, position);
}

void Mind::addObject(Object *object)
{
	if (object == nullptr) {
		err("Adding null object.");
		return;
	}
	objects.append(object);
	uidToObject[object->getUid()] = object;
}

Object *Mind::createDefaultObject(BS::Type type, QString prototype)
{
	const Prototype *proto = dataManager->getPrototype(prototype);
	Object *obj = createObject(type, prototype);
	if (proto->hasProperty(Properties::DefAnimators)){
		// May require change to some Prototype field
		for (QString anim : proto->getProperty(Properties::DefAnimators).toStringList()){
			animatorManager->addObject(anim, obj);
		}
	}

	return obj;
}

void Mind::removeObject(Object *object)
{
	qDebug() << "removeObject:" << object->getUid();
	animatorManager->removeObject(object);
	objects.removeAll(object);
	uidToObject.remove(object->getUid());
	physics->removeObject(object);
}

Object *Mind::getObjectFromUid(const int uid)
{
	if (uidToObject.contains(uid))
		return uidToObject[uid];
	else
		warn("Mind::getObjectFromUid: uid not found " + QString::number(uid));
	return nullptr;
}

const Object *Mind::getObjectFromUid(const int uid) const
{
	if (uidToObject.contains(uid))
		return uidToObject[uid];
	else
		warn("Mind::getObjectFromUid: uid not found " + QString::number(uid));
	return nullptr;
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
	//TODO remove EVERYTHING from here except creating the object itself

	Object *obj;
	switch (type) {
		case BS::Type::Invalid: {
			qDebug() << "Explosion: Invalid object type";
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
		case BS::Type::Item: {
			Item *item = new Item(dataManager->getPrototype(name));
			obj = item;
			break;
		}
		case BS::Type::Location: {
			Location *location = new Location(dataManager->getPrototype(name));
			obj = location;
			break;
		}
		case BS::Type::Unit: {
			Unit *unit = new Unit(dataManager->getPrototype(name));
			obj = unit;
			break;
		}
		default: {
			err("No such Object type.");
		}
	}

	return obj;
}

Object *Mind::createObjectFromJson(const QString &name, const QJsonObject &json)
{
	QString typeString = dataManager->getPrototype(name)->getProperty(Properties::Type).toString();
	BS::Type type = BS::changeStringToType(typeString);
	Object *obj = createObject(type, name);
	obj->loadFromJson(json);

	return obj;
}
