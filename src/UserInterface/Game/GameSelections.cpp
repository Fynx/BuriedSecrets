/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Game/GameSelections.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Location.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Effect.hpp"
#include "Mind/Mind.hpp"
#include "Mind/ObjectEffectData.hpp"
#include "UserInterface/Game/GameViewport.hpp"

GameSelections::GameSelections(Mind *m, const GameViewport &gv)
	: mind_(m),
	  gameViewport_(gv),
	  selectedLocationUid_(Object::InvalidUid)
{
	//init selectionGroups
	for (int i = 0; i < 10; ++i)
		selectionGroupsUids_.insert(i, {});
}

const QSet <int> &GameSelections::selectedUnitsUids() const
{
	return selectedUnitsUids_;
}

void GameSelections::keyPressEvent(const QKeyEvent *event)
{
	//Selection groups
	if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) {
		int groupNumber = event->key() - Qt::Key_0;

		if (event->modifiers() & Qt::ControlModifier)
			selectionGroupsUids_[groupNumber] = selectedUnitsUids_;
		else
			selectUnits(selectionGroupsUids_[groupNumber]);
	}

	//Specific unit selection
	if (event->key() >= Qt::Key_F1 && event->key() <= Qt::Key_F12) {
		int number = event->key() - Qt::Key_F1 + 1; //index from 1
		pickUnit(unitNumberToUid(number));
	}
}

void GameSelections::refresh()
{
	removeDeadUnits();
	markBuildingsSelected();
}

void GameSelections::pickUnit(int uid)
{
	if (!mind_->getPlayerFaction()->isAliveMember(uid))
		return;

	Unit *unit = mind_->getUnit(uid);
	if (unit == nullptr)
		return;

	if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
		addUnitsToSelection({unit->getUid()});
	else
		selectUnits({unit->getUid()});
}

void GameSelections::selectionByRectEnded(const QRect &selectionRect)
{
	auto filteredUnits = filterSelection(gameViewport_.objectInPixelsRect(selectionRect));

	if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
		addUnitsToSelection(filteredUnits);
	else
		selectUnits(filteredUnits);
}

int GameSelections::unitNumberToUid(int number) const
{
	auto faction = mind_->getPlayerFaction();
	auto allUnits = faction->getAllUnitsUids();

	if (number < 1 || number > allUnits.size())
		return Object::InvalidUid;

	auto uid = allUnits[number - 1];
	if (faction->isAliveMember(uid))
		return uid;

	return Object::InvalidUid;
}

QSet<int> GameSelections::filterSelection(const QSet<Object *> &objects) const
{
	QSet<int> units;
	QSet<Location *> buildings;

	for (auto &object : objects) {
		Unit *unit = dynamic_cast<Unit *>(object);
		if (unit && unit->getFactionId() == Mind::PlayerFactionId)
			units.insert(unit->getUid());

		Location *building = dynamic_cast<Location *>(object);
		if (building && building->getFactionId() == Mind::PlayerFactionId)
			buildings.insert(building);
	}

	if (units.count() > 0)
		return units;

	if (buildings.count() > 1)
		return {};

	for (auto &building : buildings) {
		for (auto &unitUid : building->getUnitsUids()) {
			Unit *unit = mind_->getUnit(unitUid);
			if (!unit)
				err("Invalid object in building");
			else
				units.insert(unit->getUid());
		}
	}
	return units;
}

void GameSelections::selectUnits(const QSet<int> &unitsUids)
{
	for (auto &uid : selectedUnitsUids_)
		removeSelectionEffect(uid);

	selectedUnitsUids_ = unitsUids;
	removeDeadUnits();

	for (auto &uid : selectedUnitsUids_)
		addSelectionEffect(uid);

	markBuildingsSelected();
}

void GameSelections::addUnitsToSelection(QSet<int> unitsUids)
{
	selectedUnitsUids_.unite(unitsUids);

	for (auto &uid : unitsUids)
		addSelectionEffect(uid);

	markBuildingsSelected();
}

void GameSelections::markBuildingsSelected()
{
	if (selectedLocationUid_ != Object::InvalidUid)
		removeSelectionEffect(selectedLocationUid_);

	selectedLocationUid_ = Object::InvalidUid;

	for (auto &uid : selectedUnitsUids_) {
		Unit *unit = mind_->getUnit(uid);
		Location *location = unit->getLocation();
		if (location) {
			if (selectedLocationUid_ == Object::InvalidUid) {
				selectedLocationUid_ = location->getUid();
				addSelectionEffect(location->getUid());
			}
			else
				if (location->getUid() != selectedLocationUid_)
					err("Probably more than 1 location selected");
		}
	}
}

void GameSelections::addSelectionEffect(int objUid)
{
	if (uidToSelectionEffect_.contains(objUid))
		return;

	Object *object = mind_->getObjectFromUid(objUid);
	if (dynamic_cast<Unit *>(object))
		emit selectionChanged(objUid, true);

	auto effectIterator = mind_->addEffect(Effect(Effects::Selection, new ObjectEffectData(object)));

	uidToSelectionEffect_.insert(objUid, effectIterator);
}

void GameSelections::removeSelectionEffect(int objUid)
{
	if (!uidToSelectionEffect_.contains(objUid))
		return;

	Unit *unit = mind_->getUnit(objUid);
	if (mind_->isNotRemoved(objUid) && unit)
		emit selectionChanged(objUid, false);

	const auto selection = uidToSelectionEffect_.find(objUid);
	mind_->deleteEffect(selection.value());

	uidToSelectionEffect_.erase(selection);
}

void GameSelections::removeDeadUnits()
{
	auto selectedUnitsUidsCopy_ = selectedUnitsUids_;
	for (auto uid : selectedUnitsUidsCopy_)
		if (!mind_->getPlayerFaction()->isAliveMember(uid)) {
			selectedUnitsUids_.remove(uid);
			removeSelectionEffect(uid);
		}
}
