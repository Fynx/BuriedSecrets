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
#include "UserInterface/IsometricPerspective.hpp"

const float SelectionManager::pixelToMetresScale = 30.0f;
const int SelectionManager::ViewportMoveDelta = 10;
const qreal SelectionManager::ViewportZoomDelta = 0.05f;

SelectionManager::SelectionManager(Mind *mind)
	: mind_(mind),
	  viewport_(new IsometricPerspective(pixelToMetresScale))
{
	//init Viewport
	viewport_.setMapSize(mind_->getMap()->getSize());

	//init selectionGroups
	for (int i = 0; i < 10; ++i)
		selectionGroups_.insert(i, {});
}

Viewport *SelectionManager::viewport()
{
	return &viewport_;
}

void SelectionManager::keyPressEvent(const QKeyEvent *event)
{
	//Viewport
	switch (event->key()) {
		case Qt::Key_W:
			viewport_.moveViewInPixels({0, ViewportMoveDelta * (-1)});
			break;
		case Qt::Key_S:
			viewport_.moveViewInPixels({0, ViewportMoveDelta});
			break;
		case Qt::Key_A:
			viewport_.moveViewInPixels({ViewportMoveDelta * (-1), 0});
			break;
		case Qt::Key_D:
			viewport_.moveViewInPixels({ViewportMoveDelta, 0});
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
		int number = event->key() - Qt::Key_0;
		if (event->modifiers() & Qt::ControlModifier)
			selectionGroups_[number] = selectedUnits_;
		else
			selectUnits(selectionGroups_[number]);
	}

	//Specific unit selection
	if (event->key() >= Qt::Key_F1 && event->key() <= Qt::Key_F12) {
		int number = event->key() - Qt::Key_F1 + 1; //index from 1
		Unit *unit = unitByNumber(number);

		if (unit != nullptr) {
			if (event->modifiers() & Qt::ShiftModifier)
				addUnitsToSelection({unit});
			else if (event->modifiers() & Qt::AltModifier) {
				for (auto &selectedUnit : selectedUnits_) {
					selectedUnit->setTargetObject(unit->getUid());
					selectedUnit->setCommand(BS::Command::Heal);
				}
			} else
				selectUnits({unit});
		}
	}
}

void SelectionManager::mousePressEvent(const QMouseEvent *event)
{
	QPointF place = viewport_.getPhysicalCoordinates(event->pos());
	Object *target = objectInPixelsPos(event->pos());

	if (event->button() == Qt::RightButton) {
		if (event->modifiers() & Qt::ControlModifier) {
			//SecondaryAction
			if (selectedUnits_.size() == 1)
			makeSecondaryAction(*selectedUnits_.begin(), place, target);
		}
		else {
			// Primary Action
			for (auto &unit : selectedUnits_)
				makePrimaryAction(unit, place, target);
		}
	}
}

void SelectionManager::gameWidgetResized(QSize sizeInPixels)
{
	viewport_.setViewSizeInPixels(sizeInPixels);
}

void SelectionManager::refresh()
{
	markBuildingsSelected();
}

void SelectionManager::addUnitToSelectionByUid(int uid)
{
	Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (unit == nullptr)
		return;
	addUnitsToSelection({unit});
}

void SelectionManager::healUnitByUid(int uid)
{
	Unit *target = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (target == nullptr)
		return;
	for (auto &unit : selectedUnits_) {
		unit->setTargetObject(target->getUid());
		unit->setCommand(BS::Command::Heal);
	}
}

void SelectionManager::selectUnitByUid(int uid)
{
	Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (unit == nullptr)
		return;
	selectUnits({unit});
}

void SelectionManager::showUnitByUid(int uid)
{
	//TODO center viewport on unit position
}

void SelectionManager::selectionByRectEnded(const QRect &selectionRect)
{
	QSet<Unit *> filteredUnits = filterSelection(objectInPixelsRect(selectionRect));

	if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
		addUnitsToSelection(filteredUnits);
	else
		selectUnits(filteredUnits);
}

void SelectionManager::makePrimaryAction(Unit *unit, QPointF point, Object *target)
{
	if (target == nullptr) {
		if (unit->getState() == BS::State::Inside) {
			unit->setCommand(BS::Command::Leave);
			unit->setTargetPoint(point);
		}
		else {
			unit->setCommand(BS::Command::Move);
			unit->setTargetPoint(point);
		}
	}
	else {
		switch (target->getType()) {
			case BS::Type::Unit:
				if (!isFriendly(target)) {
					unit->setTargetObject(target->getUid());
					unit->setCommand(BS::Command::Attack);
				}
				break;
			//TODO changed from Building/Fortification - check
			case BS::Type::Location:
				//TODO check if isFriendly
				if (unit->getState() != BS::State::Inside) {
					unit->setTargetObject(target->getUid());
					unit->setCommand(BS::Command::Enter);
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
	return mind_->getPlayerFaction()->isNeutralFaction(object->getFactionId())
	       || Mind::PlayerFactionId == object->getFactionId();
}

Unit *SelectionManager::unitByNumber(int number) const
{
	QList<int> allUnits = mind_->getPlayerFaction()->getAllUnitsUids();
	if (number < 1 || number > allUnits.size())
		return nullptr;
	return dynamic_cast<Unit *>(mind_->getObjectFromUid(allUnits[number - 1]));
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

QSet<Unit *> SelectionManager::filterSelection(const QSet<Object *> &objects) const
{
	QSet<Unit *> units;
	QSet<Location *> buildings;

	for (auto &object : objects) {
		Unit *unit = dynamic_cast<Unit *>(object);
		if (unit && unit->getFactionId() == Mind::PlayerFactionId)
			units.insert(unit);

		Location *building = dynamic_cast<Location *>(object);
		if (building && building->getFactionId() == Mind::PlayerFactionId)
			buildings.insert(building);
	}

	if (units.count() > 0)
		return units;

	for (auto &building : buildings) {
		for (auto &unitUid : building->getUnits()) {
			Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(unitUid));
			if (!unit)
				err("Invalid object in building");
			else
				units.insert(unit);
		}
	}
	return units;
}

void SelectionManager::selectUnits(const QSet<Unit *> &units)
{
	for (auto &unit : selectedUnits_) {
		unit->property(TempData::IsSelected) = QVariant(false);
		const auto selection = unitToEffect_.find(unit);
		mind_->deleteEffect(selection.value());
		unitToEffect_.erase(selection);
	}

	selectedUnits_ = units;

	for (auto &unit : selectedUnits_) {
		// TODO(Soszu): Looks like this could be extracted to a method.
		unit->property(TempData::IsSelected) = QVariant(true);
		unitToEffect_.insert(unit, mind_->addEffect(Effect(Effects::Selection, new ObjectEffectData(unit))));
	}

	markBuildingsSelected();
}

void SelectionManager::addUnitsToSelection(QSet<Unit *> units)
{
	selectedUnits_.unite(units);

	for (auto &unit : units) {
		unit->property(TempData::IsSelected) = QVariant(true);
		unitToEffect_.insert(unit, mind_->addEffect(Effect(Effects::Selection, new ObjectEffectData(unit))));
	}

	markBuildingsSelected();
}

void SelectionManager::markBuildingsSelected()
{
	for (auto &building : selectedBuildings_) {
		building->property(TempData::IsSelected) = QVariant(false);
		const auto selection = locationToEffect_.find(building);
		mind_->deleteEffect(selection.value());
		locationToEffect_.erase(selection);
	}

	selectedBuildings_.clear();

	for (auto &unit : selectedUnits_) {
		Location *building = dynamic_cast<Location *>(unit->getLocation());
		if (building) {
			building->property(TempData::IsSelected) = QVariant(true);
			selectedBuildings_.insert(building);
			locationToEffect_.insert(building, mind_->addEffect(Effect(Effects::Selection,
										   new ObjectEffectData(building))));
		}
	}
}
