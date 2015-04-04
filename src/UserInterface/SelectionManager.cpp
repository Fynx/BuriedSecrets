/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "SelectionManager.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Location.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Effect.hpp"
#include "Mind/Mind.hpp"
#include "Mind/ObjectEffectData.hpp"
#include "Mind/PointEffectData.hpp"
#include "UserInterface/BoardWidget.hpp"
#include "UserInterface/Resources.hpp"

const QColor SelectionManager::SelectionColor = QColor("Cyan");

SelectionManager::SelectionManager(Mind *mind, BoardWidget *boardWidget)
	: mind_(mind),
	  boardWidget_(boardWidget),
	  gameViewport_(mind, boardWidget),
	  selectedLocationUid_(Object::InvalidUid)
{
	// center view on camp
	gameViewport_.showObject(mind_->getObjectFromUid(mind_->getPlayerFaction()->getCampUid()));

	//init selectionGroups
	for (int i = 0; i < 10; ++i)
		selectionGroupsUids_.insert(i, {});
}

Viewport *SelectionManager::viewport()
{
	return gameViewport_.viewport();
}

void SelectionManager::keyPressEvent(const QKeyEvent *event)
{
	removeDeadFromSelection();

	//show event to gameViewport
	gameViewport_.keyPressEvent(event);

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

void SelectionManager::mousePressEvent(const QMouseEvent *event)
{
	removeDeadFromSelection();

	QPointF place = viewport()->getPhysicalCoordinates(event->pos());
	Object *target = gameViewport_.objectInPixelsPos(event->pos());

	if (event->button() == Qt::RightButton) {
		if (event->modifiers() & Qt::ControlModifier) {
			//SecondaryAction
			if (selectedUnitsUids_.size() == 1) {
				Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(*selectedUnitsUids_.begin()));
				auto command = chooseSecondaryCommand(unit, target);
				instructCommand(command, unit, place, target);
			}
		}
		else {
			// Primary Command
			for (auto &uid : selectedUnitsUids_) {
				Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
				auto command = choosePrimaryCommand(unit, target);
				instructCommand(command, unit, place, target);
			}
		}
	}
}

void SelectionManager::gameWidgetResized(QSize sizeInPixels)
{
	gameViewport_.gameWidgetResized(sizeInPixels);
}

void SelectionManager::refresh()
{
	removeDeadFromSelection();
	markBuildingsSelected();
	adjustCursor();
	checkForMoveCommand();
}

void SelectionManager::showUnit(int uid)
{
	if (!mind_->getPlayerFaction()->isAliveMember(uid))
		return;

	auto unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	auto obj = dynamic_cast<Object *>(unit);

	if (unit->getState() == BS::State::Inside)
		obj = dynamic_cast<Object *>(unit->getLocation());

	gameViewport_.showObject(obj);
}

void SelectionManager::pickUnit(int uid)
{
	if (!mind_->getPlayerFaction()->isAliveMember(uid))
		return;

	Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (unit == nullptr)
		return;

	if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
		addUnitsToSelection({unit->getUid()});
	else if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
		if (selectedUnitsUids_.size() == 1) {
			Unit *selectedUnit = dynamic_cast<Unit *>(mind_->getObjectFromUid(*selectedUnitsUids_.begin()));
			selectedUnit->setTargetObject(unit->getUid());
			selectedUnit->setCommand(BS::Command::Heal);
			mind_->addEffect(Effect(Effects::FriendlyCommand, new ObjectEffectData(unit),
			                 Effect::CommandEffectTimeout));
		}
	} else
		selectUnits({unit->getUid()});
}

void SelectionManager::selectionByRectEnded(const QRect &selectionRect)
{
	auto filteredUnits = filterSelection(gameViewport_.objectInPixelsRect(selectionRect));

	if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
		addUnitsToSelection(filteredUnits);
	else
		selectUnits(filteredUnits);
}

BS::Command SelectionManager::choosePrimaryCommand(Unit *unit, Object *target)
{
	//if unit is camp
	if (unit->getState() == BS::State::IdleBase || unit->getState() == BS::State::RunBase) {
		if (target == nullptr)
			return BS::Command::Move;
		else
			return BS::Command::None;
	}

	if (target == nullptr || target->getType() == BS::Type::Environment) {
		if (unit->getState() == BS::State::Inside)
			return BS::Command::Leave;
		else
			return BS::Command::Move;
	}
	else {
		switch (target->getType()) {
			case BS::Type::Unit:
				if (!mind_->getPlayerFaction()->isFriendly(target))
					return BS::Command::Attack;
				break;
			case BS::Type::Location:
				if (mind_->getPlayerFaction()->isFriendly(target)) {
					if (unit->getState() != BS::State::Inside)
						return BS::Command::Enter;
				}
				else
					return BS::Command::Attack;
				break;
			default:
				break;
		}
	}
	return BS::Command::None;
}

BS::Command SelectionManager::chooseSecondaryCommand(Unit *unit, Object *target)
{
	//if unit is camp
	if (unit->getState() == BS::State::IdleBase || unit->getState() == BS::State::RunBase) {
		if (target == nullptr)
			return BS::Command::Assemble;
		else
			return BS::Command::None;
	}

	if (target == nullptr) {
		if (unit->getState() != BS::State::Inside)
			return BS::Command::Assemble;
	}
	else {
		switch (target->getType()) {
			case BS::Type::Unit:
				if (mind_->getPlayerFaction()->isFriendly(target))
					return BS::Command::Heal;
				break;
			case BS::Type::Location:
				//TODO check if disassemblable - location, not fortification
				if (unit->getState() != BS::State::Inside)
					return BS::Command::Disassemble;
				break;
			default:
				break;
		}
	}
	return BS::Command::None;
}

void SelectionManager::instructCommand(BS::Command command, Unit *unit, QPointF point, Object *target)
{
	if (command != BS::Command::None)
		unit->setCommand(command);

	switch (command) {
		case BS::Command::Assemble:
			unit->setTargetPoint(point);
			return;
		case BS::Command::Attack:
			unit->setTargetObject(target->getUid());
			mind_->addEffect(Effect(Effects::HostileCommand, new ObjectEffectData(target),
			                 Effect::CommandEffectTimeout));
			return;
		case BS::Command::Disassemble:
			unit->setTargetObject(target->getUid());
			return;
		case BS::Command::Enter:
			unit->setTargetObject(target->getUid());
			mind_->addEffect(Effect(Effects::EnterCommand, new ObjectEffectData(target),
			                 Effect::CommandEffectTimeout));
			return;
		case BS::Command::Heal:
			unit->setTargetObject(target->getUid());
			mind_->addEffect(Effect(Effects::FriendlyCommand, new ObjectEffectData(target),
			                 Effect::CommandEffectTimeout));
			return;
		case BS::Command::Leave:
			return;
		case BS::Command::Move:
			unit->setTargetPoint(point);
			mind_->addEffect(Effect(Effects::MoveCommand, new PointEffectData(point), Effect::CommandEffectTimeout));
			return;
		default:
			return;
	}
}

int SelectionManager::unitNumberToUid(int number) const
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

QSet<int> SelectionManager::filterSelection(const QSet<Object *> &objects) const
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
			Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(unitUid));
			if (!unit)
				err("Invalid object in building");
			else
				units.insert(unit->getUid());
		}
	}
	return units;
}

void SelectionManager::selectUnits(const QSet<int> &unitsUids)
{
	for (auto &uid : selectedUnitsUids_)
		removeSelectionEffect(uid);

	selectedUnitsUids_ = unitsUids;

	for (auto &uid : selectedUnitsUids_)
		addSelectionEffect(uid);

	markBuildingsSelected();
}

void SelectionManager::addUnitsToSelection(QSet<int> unitsUids)
{
	selectedUnitsUids_.unite(unitsUids);

	for (auto &uid : unitsUids)
		addSelectionEffect(uid);

	markBuildingsSelected();
}

void SelectionManager::markBuildingsSelected()
{
	if (selectedLocationUid_ != Object::InvalidUid)
		removeSelectionEffect(selectedLocationUid_);

	selectedLocationUid_ = Object::InvalidUid;

	for (auto &uid : selectedUnitsUids_) {
		Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
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

void SelectionManager::addSelectionEffect(int objUid)
{
	if (uidToSelectionEffect_.contains(objUid))
		return;

	Object *object = dynamic_cast<Object *>(mind_->getObjectFromUid(objUid));
	object->property(TempData::IsSelected) = QVariant(true);
	auto effectIterator = mind_->addEffect(Effect(Effects::Selection, new ObjectEffectData(object)));

	uidToSelectionEffect_.insert(objUid, effectIterator);
}

void SelectionManager::removeSelectionEffect(int objUid)
{
	if (!uidToSelectionEffect_.contains(objUid))
		return;

	Object *object = dynamic_cast<Object *>(mind_->getObjectFromUid(objUid));
	if (object != nullptr)
		object->property(TempData::IsSelected) = QVariant(false);

	const auto selection = uidToSelectionEffect_.find(objUid);
	mind_->deleteEffect(selection.value());

	uidToSelectionEffect_.erase(selection);
}

void SelectionManager::removeDeadFromSelection()
{
	auto selectedUnitsUidsCopy_ = selectedUnitsUids_;
	for (auto uid : selectedUnitsUidsCopy_)
		if (!mind_->getPlayerFaction()->isAliveMember(uid)) {
			selectedUnitsUids_.remove(uid);
			removeSelectionEffect(uid);
		}
}

void SelectionManager::adjustCursor()
{
	// cursor not in boardWidget
	QPoint boardPos = boardWidget_->mapFromGlobal(boardWidget_->cursor().pos());
	if (!boardWidget_->geometry().contains(boardPos))
		return;

	auto target = gameViewport_.objectInPixelsPos(boardPos);
	BS::Command command = BS::Command::None;

	if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
		if (selectedUnitsUids_.size() == 1) {
			//check for possible secondary command
			Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(*selectedUnitsUids_.begin()));
			command = chooseSecondaryCommand(unit, target);
		}
	}
	else {
		if (!selectedUnitsUids_.isEmpty()) {
			//check for possible primary action
			Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(*selectedUnitsUids_.begin()));
			command = choosePrimaryCommand(unit, target);
		}
	}

	QCursor cursor = BSCursor(Cursors::PointerPrimary);

	switch (command) {
		case BS::Command::Assemble:
			cursor = BSCursor(Cursors::ArrowDownSecondary);
			break;
		case BS::Command::Attack:
			cursor = BSCursor(Cursors::Target);
			break;
		case BS::Command::Enter:
			cursor = BSCursor(Cursors::ArrowDownPrimary);
			break;
		case BS::Command::Heal:
			cursor = BSCursor(Cursors::HealCross);
			break;
		default:
			break;
	}

	boardWidget_->setCursor(cursor);
}

void SelectionManager::checkForMoveCommand()
{
	if (!(QApplication::mouseButtons() & Qt::RightButton)
	    || QApplication::keyboardModifiers() & Qt::ControlModifier)
		return;

	QPoint pos = boardWidget_->mapFromGlobal(boardWidget_->cursor().pos());
	if (!boardWidget_->geometry().contains(pos))
		return;

	QPointF place = viewport()->getPhysicalCoordinates(pos);
	Object *target = gameViewport_.objectInPixelsPos(pos);

	if (target != nullptr && target->getType() != BS::Type::Environment)
		return;

	for (auto &uid : selectedUnitsUids_) {
		Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
		if (unit->getCommand() == BS::Command::Move) {
			unit->setCommand(BS::Command::Move);
			unit->setTargetPoint(place);
		}
	}
}
