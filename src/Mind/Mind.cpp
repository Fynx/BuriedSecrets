/* YoLoDevelopment, 2014-2015
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
	  showPathsEffectOn(false)
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

	//WARNING ItemConstructor is NOT used. Because what for.

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
				Object *j = getObjectFromUid(faction->getJournalUid());
				Q_ASSERT(j->getType() == BS::Type::Journal);
				faction->setJournal(dynamic_cast<Journal *>(j));
				qDebug() << "\t\t\tcontains journal (" << j->getUid() << ")";
			}

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
			Object *eq = getObjectFromUid(eqUid);
			Q_ASSERT(eq->getType() == BS::Type::Equipment);
			unit->setEquipment(dynamic_cast<Equipment *>(eq));

			break;
		}
		case BS::Type::Equipment: {
			Equipment *eq = dynamic_cast<Equipment *>(object);

			for (int itemUid : eq->getItemsUids()) {
				Object *item = getObjectFromUid(itemUid);
				Q_ASSERT(item->getType() == BS::Type::Item);
				eq->addItem(dynamic_cast<Item *>(item));
			}
			for (BS::Slot slot : BS::getSlots()) {
				int itemUid = eq->getSlotItemUid(slot);
				if (itemUid != Object::InvalidUid) {
					Object *item = getObjectFromUid(itemUid);
					Q_ASSERT(item->getType() == BS::Type::Item);
					eq->putItemIntoSlot(slot, dynamic_cast<Item *>(item));
				}
			}

			break;
		}
		case BS::Type::Location: {
			Location *loc = dynamic_cast<Location *>(object);

			for (int itemUid : loc->getItemsUids().keys()) {
				Item *item = dynamic_cast<Item *>(getObjectFromUid(itemUid));
				Q_ASSERT(item->getType() == BS::Type::Item);
				loc->addItem(loc->getItemsUids()[itemUid], item);

				for (Item *item : loc->getItemsDifficulty().keys())
					qDebug() << "\t\t\tcontains item" << item->getName()
						<< "with search difficulty" << loc->getItemsDifficulty()[item];
			}
			for (int unitUid : loc->getUnitsUids()) {
				loc->insertUnit(unitUid);
				Object *unit = getObjectFromUid(unitUid);
				Q_ASSERT(unit->getType() == BS::Type::Unit);
				dynamic_cast<Unit *>(unit)->setLocation(loc);
			}

			break;
		}
		case BS::Type::Journal: {
			Journal *journal = dynamic_cast<Journal *>(object);

			for (int entryUid : journal->getEntriesUids()) {
				JournalEntry *entry = dynamic_cast<JournalEntry *>(getObjectFromUid(entryUid));
				Q_ASSERT(entry->getType() == BS::Type::JournalEntry);
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
	addEffect(
		Effect(
			Effects::Antipsychosis,
			new ObjectRadiusEffectData(getObjectFromUid(
				getFactionById(PlayerFactionId)->getCampUid()),
				getFactionById(PlayerFactionId)->getCampRange())));

	info("done.");
}

QJsonObject Mind::saveToJson() const
{
	QJsonObject json;
	QJsonArray objs;

	json.insert(MapProperties::MapName, mapManager->getMap()->getName());
	json.insert(MapProperties::MapDesc, mapManager->getMap()->getDesc());
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
	activeEffects.erase(effectIterator);
}

void Mind::toggleBasePolygons()
{
	// Remove all occurences of base polygons.
	removeAllEffects(Effects::BasePolygon);

	if (!basePolygonsEffectOn) {
		// Add base polygons to everything.
		for (const auto *object : objects) {
			addEffect(Effect{Effects::BasePolygon, new ObjectEffectData{object}});
		}
	}

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

void Mind::addObject(Object *object, const QPointF &position, float angle)
{
	addObject(object);
	physics->addObject(object, position, angle);
	if (mapManager != nullptr) {
		mapManager->addObject(object);
	}

	if (object->getType() == BS::Type::Unit) {
		addEffect(Effect{Effects::UnitShadow, new ObjectEffectData{object}});
	}
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
	const auto position = physics->getPosition(object);
	animatorManager->removeObject(object);
	physics->removeObject(object);
	if (mapManager != nullptr) {
		mapManager->removeObject(object, position);
	}
	objects.removeAll(object);
	uidToObject.remove(object->getUid());

	if (object->getType() == BS::Type::Unit)
		removeObject(dynamic_cast<Unit *>(object)->getEquipment());
	if (object->getType() == BS::Type::Faction)
		removeObject(dynamic_cast<Faction *>(object)->getEquipment());
	if (object->getType() == BS::Type::Equipment)
		for (Item *item : dynamic_cast<Equipment *>(object)->getItems())
			removeObject(item);
}

bool Mind::isNotRemoved(int uid) const
{
	return uidToObject.contains(uid);
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

QVector<const Object *> Mind::getAllObjects() const
{
	QVector<const Object *> result;
	for (Object * obj : objects) {
		result.append(obj);
	}
	return result;
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
	Unit *unit = dynamic_cast<Unit*>(getObjectFromUid(uid));
	if (!unit)
		return;
	getFactionById(unit->getFactionId())->removePendingUnit(uid);
	getFactionById(unit->getFactionId())->addUnit(uid);
}

void Mind::declinePendingUnit(int uid)
{
	Unit *unit = dynamic_cast<Unit*>(getObjectFromUid(uid));
	if (!unit)
		return;
	getFactionById(unit->getFactionId())->removePendingUnit(uid);
	removeObject(unit);
}

Object *Mind::createObject(BS::Type type, const QString &name)
{
	//TODO remove EVERYTHING from here except creating the object itself

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
			activeEffects.erase(it);
		it = iter;
	}
}
