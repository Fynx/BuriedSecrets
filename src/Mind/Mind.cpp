﻿/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Mind.hpp"

#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
#include "DebugManager/DebugManager.hpp"
#include "Mind/Animators/AnimatorManager.hpp"
#include "Mind/ItemConstructor.hpp"
#include "Mind/MapManager/MapManager.hpp"
#include "Mind/ObjectRadiusEffectData.hpp"
#include "GameObjects/Environment.hpp"
#include "GameObjects/Equipment.hpp"
#include "GameObjects/Journal.hpp"
#include "GameObjects/Location.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Quest.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "SoundsManager/SoundsManager.hpp"

const int Mind::PlayerFactionId = 1;

Mind::Mind(DataManager *dataManager, PhysicsEngine *physicsEngine, SoundsManager *soundsManager)
	: dataManager(dataManager),
	  physics(physicsEngine),
	  soundsManager(soundsManager),
	  animatorManager(new AnimatorManager(this)),
	  mapManager(nullptr),
	  constructor(new ItemConstructor(dataManager, this)),
	  gameState(BS::GameState::Running),
	  basePolygonsEffectOn(false),
	  showPathsEffectOn(false),
	  secsSinceBeginning(0)
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

AnimatorManager *Mind::getAnimatorManager()
{
	return animatorManager;
}

void Mind::loadFromJson(const QJsonObject &json)
{
	delete mapManager;

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

	info("Binding objects...");

	int objectsSize = objects.size();
	for (int i = 0; i < objectsSize; ++i) {
		Object *object = objects[i];
		qDebug() << "\t" << object->getName();
		switch (object->getType()) {
		case BS::Type::Faction: {
			Faction *faction = dynamic_cast<Faction *>(object);

			factions.insert(object->getFactionId(), faction);
			for (int objectUid : faction->getUnitsUids()) {
				getObjectFromUid(objectUid)->setFactionId(object->getFactionId());
			}

			int eqUid = faction->getEquipmentUid();
			if (eqUid == Object::InvalidUid) {
				Object *eq = createObject(BS::Type::Equipment, BasicPrototypes::BasicEquipment);
				eqUid = eq->assignUid();
				addObject(eq);
			}
			Object *eq = getObjectFromUid(eqUid);
			Q_ASSERT(eq->getType() == BS::Type::Equipment);
			faction->setEquipment(dynamic_cast<Equipment *>(eq));

			if (faction->getJournalUid() != Object::InvalidUid) {
				Journal *j = getJournal(faction->getJournalUid());
				faction->setJournal(j);
				qDebug() << "\t\t\tcontains journal (" << j->getUid() << ")";
			}

			for (int quest : faction->getQuests())
				qDebug() << "\t\t\tcontains quest" << quest;

			break;
		}
		case BS::Type::Unit: {
			Unit *unit = dynamic_cast<Unit *>(object);

			int eqUid = unit->getEquipmentUid();
			if (eqUid == Object::InvalidUid) {
				Object *eq = createObject(BS::Type::Equipment, BasicPrototypes::BasicEquipment);
				eqUid = eq->assignUid();
				addObject(eq);
			}
			unit->setEquipment(getEquipment(eqUid));

			break;
		}
		case BS::Type::Equipment: {
			Equipment *eq = dynamic_cast<Equipment *>(object);

			for (int itemUid : eq->getItemsUids())
				eq->addItem(getItem(itemUid));
			for (BS::Slot slot : BS::getSlots()) {
				int itemUid = eq->getSlotItemUid(slot);
				if (itemUid != Object::InvalidUid)
					eq->putItemIntoSlot(slot, getItem(itemUid));
			}

			break;
		}
		case BS::Type::Location: {
			Location *loc = dynamic_cast<Location *>(object);

			for (int itemUid : loc->getItemsUids().keys()) {
				loc->addItem(loc->getItemsUids()[itemUid], getItem(itemUid));

				for (Item *item : loc->getItemsDifficulty().keys())
					qDebug() << "\t\t\tcontains item" << item->getName()
						<< "with search difficulty" << loc->getItemsDifficulty()[item];
			}
			for (int unitUid : loc->getUnitsUids()) {
				qDebug() << "\t\t\tcontains unit" << unitUid;
				loc->insertUnit(unitUid);
				getUnit(unitUid)->setLocation(loc);
				getUnit(unitUid)->setState(BS::State::Inside);
			}

			break;
		}
		case BS::Type::Journal: {
			Journal *journal = dynamic_cast<Journal *>(object);

			for (int entryUid : journal->getEntriesUids()) {
				JournalEntry *entry = getJournalEntry(entryUid);
				journal->addEntry(entry);
				qDebug() << "\t\t\tcontains entry" << entry->getTitle() << "("
					<< BS::changeEntryTypeToString(entry->getEntryType()) << ")";
			}

			break;
		}
		case BS::Type::JournalEntry: {
			/**
			 * Note that you can also take a quest entry from here. (wtf?!)
			 */
			JournalEntry *entry = dynamic_cast<JournalEntry *>(object);

			if (entries.contains(entry->getEntryType()))
				;
// 				err("Duplicate entry types.");
			else
				entries[entry->getEntryType()] = entry;

			break;
		}
		default:;
		}
	}

	// It is important that this line is called AFTER the creation of objects.
	mapManager = new MapManager(json, this, physics, PlayerFactionId);

	// Add antipsychosis.
	const Faction *playerFaction = getFactionById(PlayerFactionId);
	const Object *camp = getObjectFromUid(playerFaction->getCampUid());
	const float campRange = playerFaction->getCampRange();

	addEffect(Effect(Effects::Antipsychosis, new ObjectRadiusEffectData(camp, campRange)));

	// Add visibility for the camp.
	// Get the radius for the camp:
	float radius = 0.0f;
	const auto polygon = camp->getPrototype()->getBasePolygon();
	const auto centre = camp->getPrototype()->getBaseCentre();
	for (const auto &p : polygon)
		radius = qMax(radius, BS::Geometry::distance(centre, p));
	mapManager->addVisibility(BS::Geometry::Circle(physics->getPosition(camp), radius * 1.5f), PlayerFactionId);

	info("done.");
}

QJsonObject Mind::saveToJson() const
{
	QJsonObject json;
	QJsonArray objs;

	json.insert(MapProperties::MapName, mapManager->getMap()->getName());
	json.insert(MapProperties::MapDesc, mapManager->getMap()->getDesc());
	json.insert(MapProperties::MapTitle, mapManager->getMap()->getTitle());
	json.insert(MapProperties::MapText, mapManager->getMap()->getText());
	json.insert(MapProperties::MapWidth,  mapManager->getMap()->getSize().width());
	json.insert(MapProperties::MapHeight, mapManager->getMap()->getSize().height());

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

BS::GameState Mind::getGameState() const
{
	return gameState;
}

void Mind::setGameState(BS::GameState gameState)
{
	this->gameState = gameState;
}

QLinkedList<Effect> * const Mind::getActiveEffects()
{
	return &activeEffects;
}

QLinkedList<Effect>::iterator Mind::addEffect(const Effect &effect)
{
	return activeEffects.insert(activeEffects.end(), effect);
}

void Mind::deleteEffect(QLinkedList<Effect>::iterator effectIterator)
{
	effectIterator->destroyData();
	activeEffects.erase(effectIterator);
}

void Mind::toggleBasePolygons()
{
	// Remove all occurences of base polygons.
	removeAllEffects(Effects::BasePolygon);

	if (!basePolygonsEffectOn)
		// Add base polygons to everything.
		for (const auto *object : objects)
			addEffect(Effect{Effects::BasePolygon, new ObjectEffectData{object}});

	basePolygonsEffectOn = !basePolygonsEffectOn;
}

void Mind::toggleShowPaths()
{
	// Remove all occurences of show paths.
	removeAllEffects(Effects::ShowPath);

	if (!showPathsEffectOn) {
		// Add base polygons to everything.
		for (const auto *object : objects) {
			if (object->getType() == BS::Type::Unit) {
				addEffect(Effect{Effects::ShowPath, new ObjectEffectData{object}});
			}
		}
	}

	showPathsEffectOn = !showPathsEffectOn;
}

int Mind::getSecsSinceBeginning() const
{
	return secsSinceBeginning;
}

void Mind::incSecsSinceBeginning()
{
	++secsSinceBeginning;
}

void Mind::addObject(Object *object, const QPointF &position, float angle)
{
	addObject(object);
	physics->addObject(object, position, angle);
	if (mapManager != nullptr)
		mapManager->addObject(object);

	if (object->getType() == BS::Type::Unit)
		addEffect(Effect{Effects::UnitShadow, new ObjectEffectData{object}});
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
	obj->assignUid();
	if (proto->hasProperty(Properties::DefAnimators))
		// May require change to some Prototype field
		for (const QString &anim : proto->getProperty(Properties::DefAnimators).toStringList())
			animatorManager->addObject(anim, obj);

	return obj;
}

void Mind::removeObject(Object *object)
{
	qDebug() << "removeObject:" << object->getUid();
	const auto position = physics->getPosition(object);
	animatorManager->removeObject(object);
	physics->removeObject(object);
	if (mapManager != nullptr)
		mapManager->removeObject(object, position);
	objects.removeAll(object);
	uidToObject.remove(object->getUid());

	if (object->getType() == BS::Type::Unit)
		removeObject(dynamic_cast<Unit *>(object)->getEquipment());
	if (object->getType() == BS::Type::Faction)
		removeObject(dynamic_cast<Faction *>(object)->getEquipment());
	if (object->getType() == BS::Type::Equipment)
		for (Item *item : dynamic_cast<Equipment *>(object)->getItems())
			removeObject(item);

	delete object;
}

bool Mind::isNotRemoved(int uid) const
{
	return uidToObject.contains(uid);
}

// Warnings about no objects muted and changed to info.

Object *Mind::getObjectFromUid(const int uid)
{
	if (uidToObject.contains(uid))
		return uidToObject[uid];
// 	else
// 		info("Mind::getObjectFromUid: uid not found " + QString::number(uid));
	return nullptr;
}

const Object *Mind::getObjectFromUid(const int uid) const
{
	if (uidToObject.contains(uid))
		return uidToObject[uid];
// 	else
// 		info("Mind::getObjectFromUid: uid not found " + QString::number(uid));
	return nullptr;
}

Faction *Mind::getFactionById(int id)
{
// 	if (!factions.contains(id))
// 		qDebug() << "No such Faction! " << id;
	return factions.value(id);
}

const Faction *Mind::getFactionById(int id) const
{
// 	if (!factions.contains(id))
// 		qDebug() << "No such Faction! " << id;
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

QVector<const Object *> Mind::getAllObjects() const
{
	QVector<const Object *> result;
	for (Object * obj : objects) {
		result.append(obj);
	}
	return result;
}

Equipment *Mind::getEquipment(const int uid)
{
	Equipment *eq = dynamic_cast<Equipment *>(getObjectFromUid(uid));
	if (!eq)
		err("Equipment with uid " + QString::number(uid) + " not found!");
	return eq;
}

Item *Mind::getItem(const int uid)
{
	Item *item = dynamic_cast<Item *>(getObjectFromUid(uid));
	if (!item)
		err("Item with uid " + QString::number(uid) + " not found!");
	return item;
}

Journal *Mind::getJournal(const int uid)
{
	Journal *journal = dynamic_cast<Journal *>(getObjectFromUid(uid));
	if (!journal)
		err("Journal with uid " + QString::number(uid) + " not found!");
	return journal;
}

JournalEntry *Mind::getJournalEntry(const int uid)
{
	JournalEntry *entry = dynamic_cast<JournalEntry *>(getObjectFromUid(uid));
	if (!entry)
		err("Item with uid " + QString::number(uid) + " not found!");
	return entry;
}

Location *Mind::getLocation(const int uid)
{
	Location *location = dynamic_cast<Location *>(getObjectFromUid(uid));
	if (!location)
		err("Item with uid " + QString::number(uid) + " not found!");
	return location;
}

Quest *Mind::getQuest(const int uid)
{
	Quest *quest = dynamic_cast<Quest *>(getObjectFromUid(uid));
	if (!quest)
		err("Item with uid " + QString::number(uid) + " not found!");
	return quest;
}

Unit *Mind::getUnit(const int uid)
{
	Unit *unit = dynamic_cast<Unit *>(getObjectFromUid(uid));
	if (!unit)
		err("Item with uid " + QString::number(uid) + " not found!");
	return unit;
}

const Unit *Mind::getUnit(const int uid) const
{
	const Unit *unit = dynamic_cast<const Unit *>(getObjectFromUid(uid));
	if (!unit)
		err("Item with uid " + QString::number(uid) + " not found!");
	return unit;
}

JournalEntry *Mind::getEntryFromType(EntryType type)
{
	if (!entries.contains(type)) {
		warn("There is no entry with type " + BS::changeEntryTypeToString(type));
		return nullptr;
	}
	return entries[type];
}

// FactionId should be set during adding to the pending set in faction
void Mind::acceptPendingUnit(int uid)
{
	Unit *unit = getUnit(uid);
	if (!unit)
		return;
	getFactionById(unit->getFactionId())->removePendingUnit(uid);
	getFactionById(unit->getFactionId())->addUnit(uid);
}

void Mind::declinePendingUnit(int uid)
{
	Unit *unit = getUnit(uid);
	if (!unit)
		return;
	getFactionById(unit->getFactionId())->removePendingUnit(uid);
	removeObject(unit);
}

Object *Mind::createObject(BS::Type type, const QString &name)
{
	Object *obj;
	switch (type) {
		case BS::Type::Invalid: {
			err("Explosion: Invalid object type (name=" + name + ")");
			break;
		}
		case BS::Type::Environment: {
			Environment *environment = new Environment(dataManager->getPrototype(name));
			obj = environment;
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
		case BS::Type::Journal: {
			Journal *journal = new Journal(dataManager->getPrototype(name));
			obj = journal;
			break;
		}
		case BS::Type::JournalEntry: {
			JournalEntry *entry = new JournalEntry(dataManager->getPrototype(name));
			obj = entry;
			break;
		}
		case BS::Type::Location: {
			Location *location = new Location(dataManager->getPrototype(name));
			obj = location;
			break;
		}
		case BS::Type::Quest: {
			Quest *quest = new Quest(dataManager->getPrototype(name));
			obj = quest;
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

void Mind::removeAllEffects(const QString &name)
{
	for (auto it = activeEffects.begin(); it != activeEffects.end();) {
		auto iter = it;
		++iter;
		if (it->getName() == name)
			deleteEffect(it);
		it = iter;
	}
}
