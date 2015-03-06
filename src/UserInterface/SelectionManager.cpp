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
#include "UserInterface/IsometricPerspective.hpp"
#include "UserInterface/Resources.hpp"

const float SelectionManager::pixelToMetresScale = 30.0f;
const int SelectionManager::ViewportKeyMoveDelta = 300;
const int SelectionManager::ViewportEdgeMoveDelta = 15;
const int SelectionManager::EdgeViewportMoveTimerInterval = 10;
const qreal SelectionManager::ViewportZoomDelta = 0.05f;
const QColor SelectionManager::SelectionColor = QColor("Cyan");

SelectionManager::SelectionManager(Mind *mind, BoardWidget *boardWidget)
	: mind_(mind),
	  boardWidget_(boardWidget),
	  viewport_(new IsometricPerspective(pixelToMetresScale)),
	  edgeMoveTimer_(new QTimer),
	  selectedLocationUid_(Object::InvalidUid)
{
	//init Viewport
	viewport_.setMapSize(mind_->getMap()->getSize());

	connect(edgeMoveTimer_, &QTimer::timeout, this, &SelectionManager::checkForViewportMove);

	edgeMoveTimer_->start(EdgeViewportMoveTimerInterval);

	//init selectionGroups
	for (int i = 0; i < 10; ++i)
		selectionGroupsUids_.insert(i, {});
}

Viewport *SelectionManager::viewport()
{
	return &viewport_;
}

void SelectionManager::keyPressEvent(const QKeyEvent *event)
{
	removeDeadFromSelection();

	//Viewport
	switch (event->key()) {
		case Qt::Key_W:
			viewport_.moveViewInPixels({0, ViewportKeyMoveDelta * (-1)});
			break;
		case Qt::Key_S:
			viewport_.moveViewInPixels({0, ViewportKeyMoveDelta});
			break;
		case Qt::Key_A:
			viewport_.moveViewInPixels({ViewportKeyMoveDelta * (-1), 0});
			break;
		case Qt::Key_D:
			viewport_.moveViewInPixels({ViewportKeyMoveDelta, 0});
			break;
		case Qt::Key_Plus:
			viewport_.zoomIn(ViewportZoomDelta);
			break;
		case Qt::Key_Minus:
			viewport_.zoomIn(ViewportZoomDelta * (-1));
			break;
		case Qt::Key_Equal:
			viewport_.resetZoom();
			break;
	}

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

	QPointF place = viewport_.getPhysicalCoordinates(event->pos());
	Object *target = objectInPixelsPos(event->pos());

	if (event->button() == Qt::RightButton) {
		if (event->modifiers() & Qt::ControlModifier) {
			//SecondaryAction
			if (selectedUnitsUids_.size() == 1) {
				Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(*selectedUnitsUids_.begin()));
				makeSecondaryAction(unit, place, target);
			}
		}
		else {
			// Primary Action
			for (auto &uid : selectedUnitsUids_) {
				Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
				makePrimaryAction(unit, place, target);
			}
		}
	}
}

void SelectionManager::gameWidgetResized(QSize sizeInPixels)
{
	viewport_.setViewSizeInPixels(sizeInPixels);
}

void SelectionManager::refresh()
{
	removeDeadFromSelection();
	markBuildingsSelected();
	adjustCursor();
	checkForMoveCommand();
	checkForViewportMove();
}

void SelectionManager::showUnit(int uid)
{
	if (!mind_->getPlayerFaction()->isAliveMember(uid))
		return;

	//TODO center viewport on unit
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
	auto filteredUnits = filterSelection(objectInPixelsRect(selectionRect));

	if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
		addUnitsToSelection(filteredUnits);
	else
		selectUnits(filteredUnits);
}

void SelectionManager::makePrimaryAction(Unit *unit, QPointF point, Object *target)
{
	if (target == nullptr) {
		if (unit->getState() == BS::State::Inside)
			unit->setCommand(BS::Command::Leave);
		else
			unit->setCommand(BS::Command::Move);

		unit->setTargetPoint(point);
		mind_->addEffect(Effect(Effects::MoveCommand, new PointEffectData(point), Effect::CommandEffectTimeout));
	}
	else {
		switch (target->getType()) {
			case BS::Type::Unit:
				if (!isFriendly(target)) {
					unit->setTargetObject(target->getUid());
					unit->setCommand(BS::Command::Attack);
					mind_->addEffect(Effect(Effects::HostileCommand, new ObjectEffectData(target),
					                 Effect::CommandEffectTimeout));
				}
				break;
			//TODO changed from Building/Fortification - check
			case BS::Type::Location:
				//TODO check if isFriendly
				if (unit->getState() != BS::State::Inside) {
					unit->setTargetObject(target->getUid());
					unit->setCommand(BS::Command::Enter);
					mind_->addEffect(Effect(Effects::EnterCommand, new ObjectEffectData(target),
					                 Effect::CommandEffectTimeout));
				}
				break;
			default:
				break;
		}
	}
}

void SelectionManager::makeSecondaryAction(Unit *unit, QPointF point, Object *target)
{
	if (target == nullptr) {
		if (unit->getState() != BS::State::Inside) {
			unit->setCommand(BS::Command::Assemble);
			unit->setTargetPoint(point);
		}
	}
	else {
		switch (target->getType()) {
			case BS::Type::Unit:
				if (isFriendly(target)) {
					unit->setTargetObject(target->getUid());
					unit->setCommand(BS::Command::Heal);
					mind_->addEffect(Effect(Effects::FriendlyCommand, new ObjectEffectData(target),
					                 Effect::CommandEffectTimeout));
				}
				break;
			case BS::Type::Location:
				//TODO check if disassemblable - location, not fortification
				if (unit->getState() != BS::State::Inside) {
					unit->setTargetObject(target->getUid());
					unit->setCommand(BS::Command::Disassemble);
				}
				break;
			default:
				break;
		}
	}
}

bool SelectionManager::isFriendly(Object* object)
{
	//TODO move to faction?
	return mind_->getPlayerFaction()->isNeutralFaction(object->getFactionId())
	       || Mind::PlayerFactionId == object->getFactionId();
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

Object *SelectionManager::objectInPixelsPos(QPoint pointInPixels) const
{
	QPointF point = viewport_.getPhysicalCoordinates(pointInPixels);

	point -= QPointF(0.1, 0.1);
	QList<const Object *> objects = mind_->physicsEngine()->getObjectsInRect(QRectF(point, QSizeF{0.2, 0.2}));

	if (objects.isEmpty())
		return nullptr;

	return mind_->getObjectFromUid(objects[0]->getUid());
}

QSet<Object *> SelectionManager::objectInPixelsRect(QRect rectInPixels) const
{
	auto topLeftInMetres = viewport_.getPhysicalCoordinates(rectInPixels.topLeft());
	auto botomRightInMetres = viewport_.getPhysicalCoordinates(rectInPixels.bottomRight());
	QRectF rectInMetres(topLeftInMetres, botomRightInMetres);
	rectInMetres = rectInMetres.normalized();

	QList<const Object *> objects = mind_->physicsEngine()->getObjectsInRect(rectInMetres);

	QSet<Object *> result;
	for (auto &obj : objects)
		result.insert(mind_->getObjectFromUid(obj->getUid()));

	return result;
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
	Object *object = dynamic_cast<Object *>(mind_->getObjectFromUid(objUid));
	object->property(TempData::IsSelected) = QVariant(true);
	auto effectIterator = mind_->addEffect(Effect(Effects::Selection, new ObjectEffectData(object)));

	uidToSelectionEffect_.insert(objUid, effectIterator);
}

void SelectionManager::removeSelectionEffect(int objUid)
{
	Object *object = dynamic_cast<Object *>(mind_->getObjectFromUid(objUid));
	object->property(TempData::IsSelected) = QVariant(false);

	const auto selection = uidToSelectionEffect_.find(objUid);
	mind_->deleteEffect(selection.value());

	uidToSelectionEffect_.erase(selection);
}

void SelectionManager::removeDeadFromSelection()
{
	auto selectedUnitsUidsCopy_ = selectedUnitsUids_;
	for (auto uid : selectedUnitsUidsCopy_)
		if (!mind_->getPlayerFaction()->isAliveMember(uid))
			selectedUnitsUids_.remove(uid);
}

void SelectionManager::adjustCursor()
{
	// cursor not in boardWidget
	QPoint boardPos = boardWidget_->mapFromGlobal(boardWidget_->cursor().pos());
	if (!boardWidget_->geometry().contains(boardPos))
		return;

	// no units selected
	if (selectedUnitsUids_.isEmpty()) {
		boardWidget_->setCursor(BSCursor((Cursors::PointerPrimary)));
		return;
	}

	// check if only one unit
	Unit *unit = nullptr;
	if (selectedUnitsUids_.size() == 1)
		unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(*selectedUnitsUids_.begin()));

	// set default cursor
	QCursor cursor = BSCursor(Cursors::PointerPrimary);

	// adjust cursor
	auto obj = objectInPixelsPos(boardPos);
	Location *l;
	if (obj != nullptr) {
		switch (obj->getType()) {
			case BS::Type::Location:
				l = dynamic_cast<Location *>(obj);
				// check for etering location
				if (isFriendly(obj)) {
					if (l->getCapacity() - l->getUnitsUids().size() > 0)
						cursor = BSCursor(Cursors::ArrowDownPrimary);
				}
				else
					//check for hostile location attack
					cursor = BSCursor(Cursors::Target);
				break;
			case BS::Type::Unit:
				// check for heal
				if (isFriendly(obj)) {
					if (QApplication::keyboardModifiers() & Qt::ControlModifier && unit != nullptr)
						if (unit->getEquipment()->getSlotItem(BS::Medicament) != nullptr)
							cursor = BSCursor(Cursors::HealCross);
				}
				else
					//check for hostile unit attack
					cursor = BSCursor(Cursors::Target);
				break;
			default:
				break;
		}
	}
	else
		// check for contruction placement
		if (QApplication::keyboardModifiers() & Qt::ControlModifier && unit != nullptr) {
			if (unit->getEquipment()->getSlotItem(BS::Fortification) != nullptr)
				cursor = BSCursor(Cursors::ArrowDownSecondary);
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

	QPointF place = viewport_.getPhysicalCoordinates(pos);
	Object *target = objectInPixelsPos(pos);

	if (target != nullptr)
		return;

	for (auto &uid : selectedUnitsUids_) {
		Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
		if (unit->getCommand() == BS::Command::Move) {
			unit->setCommand(BS::Command::Move);
			unit->setTargetPoint(place);
		}
	}
}

void SelectionManager::checkForViewportMove()
{
	QPoint pos = boardWidget_->cursor().pos();
	QRect global = QApplication::desktop()->screenGeometry();

	if (pos.x() == global.right())
		viewport_.moveViewInPixels({ViewportEdgeMoveDelta, 0});

	if (pos.x() == global.left())
		viewport_.moveViewInPixels({(-1) * ViewportEdgeMoveDelta, 0});

	if (pos.y() == global.bottom())
		viewport_.moveViewInPixels({0, ViewportEdgeMoveDelta});

	if (pos.y() == global.top())
		viewport_.moveViewInPixels({0, (-1) * ViewportEdgeMoveDelta});
}
