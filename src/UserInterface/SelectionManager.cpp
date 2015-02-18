/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "SelectionManager.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Building.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
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
	case Qt::Key_P:
		if (isPaused_)
			mind_->resumeGame();
		else
			mind_->pauseGame();
		isPaused_ = !isPaused_;
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
	QPointF place = viewport_.fromPixelsToMetres(event->pos());
	Object *target = objectInPixelsPos(event->pos());

	//Selection TODO see if still needed
	if (event->button() == Qt::LeftButton) {
		if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
			if (target != nullptr)
				addUnitsToSelection(filterSelection({target}));
		}
		else {
			if (target == nullptr)
				selectUnits({});
			else
				selectUnits(filterSelection({target}));
		}
	}

	//Commands
	if (event->button() == Qt::RightButton) {
		for (auto &unit : selectedUnits_) {
			if (QApplication::keyboardModifiers() & Qt::AltModifier) {
				unit->setTargetObject(target->getUid());
				unit->setCommand(BS::Command::Heal);
			}
			else {
				if (target == nullptr) {
					//TODO it should be via MapManager; only setting destination point
					QPointF pos = QPointF(unit->property(TempData::X).toDouble(),
					                      unit->property(TempData::Y).toDouble());
					unit->setCurrentPath(mind_->getMapManager()->getPath(pos, place));
					if (unit->getState() == BS::State::Inside) {
						unit->setCommand(BS::Command::LeaveBuilding);
						qDebug() << "LeaveBuilding   http://ujeb.se/UuzV";
					}
					else
						unit->setCommand(BS::Command::Move);
				}
				else {
					if (target->getType() == BS::Type::Unit) {
						unit->setTargetObject(target->getUid());
						unit->setCommand(BS::Command::Attack);
					}
					else {
						if (target->getType() == BS::Type::Building) {
							unit->setTargetObject(target->getUid());
							unit->setCommand(BS::Command::EnterBuilding);
						}
					}
				}
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
	qDebug() << selectionRect;
	QSet<Unit *> filteredUnits = filterSelection(objectInPixelsRect(selectionRect));

	if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
		addUnitsToSelection(filteredUnits);
	else
		selectUnits(filteredUnits);
}

Unit *SelectionManager::unitByNumber(int number) const
{
	QList<int> allUnits = mind_->getPlayerFaction()->getAllUnits();
	if (number < 1 || number > allUnits.size())
		return nullptr;
	return dynamic_cast<Unit *>(mind_->getObjectFromUid(allUnits[number - 1]));
}

Object *SelectionManager::objectInPixelsPos(QPoint pointInPixels) const
{
	QPointF point = viewport_.fromPixelsToMetres(pointInPixels);

	point -= QPointF(0.1, 0.1);
	QList<const Object *> objects = mind_->physicsEngine()->getObjectsInRect(QRectF(point, QSizeF{0.2, 0.2}));

	if (objects.isEmpty())
		return nullptr;

	return mind_->getObjectFromUid(objects[0]->getUid());
}

QSet<Object *> SelectionManager::objectInPixelsRect(QRect rectInPixels) const
{
	auto topLeftInMetres = viewport_.fromPixelsToMetres(rectInPixels.topLeft());
	auto botomRightInMetres = viewport_.fromPixelsToMetres(rectInPixels.bottomRight());
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
	QSet<Building *> buildings;

	for (auto &object : objects) {
		Unit *unit = dynamic_cast<Unit *>(object);
		if (unit && unit->getFactionId() == Mind::PlayerFactionId)
			units.insert(unit);

		Building *building = dynamic_cast<Building *>(object);
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
	for (auto &unit : selectedUnits_)
		unit->property(TempData::IsSelected) = QVariant(false);

	selectedUnits_ = units;

	for (auto &unit : selectedUnits_)
		unit->property(TempData::IsSelected) = QVariant(true);

	markBuildingsSelected();
}

void SelectionManager::addUnitsToSelection(QSet<Unit *> units)
{
	selectedUnits_.unite(units);

	for (auto &unit : units)
		unit->property(TempData::IsSelected) = QVariant(true);

	markBuildingsSelected();
}

void SelectionManager::markBuildingsSelected()
{
	for (auto &building : selectedBuildings_)
		building->property(TempData::IsSelected) = QVariant(false);

	selectedBuildings_.clear();

	for (auto &unit : selectedUnits_) {
		Building *building = dynamic_cast<Building *>(unit->getLocation());
		if (building) {
			building->property(TempData::IsSelected) = QVariant(true);
			selectedBuildings_.insert(building);
		}
	}
}
