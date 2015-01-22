/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "GameWidgetManager.hpp"

#include "Common/Strings.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/IsometricPerspective.hpp"

const float GameWidgetManager::pixelToMetresScale = 30.0f;
const int GameWidgetManager::ViewportMoveDelta = 10;
const qreal GameWidgetManager::ViewportZoomDelta = 0.05f;

GameWidgetManager::GameWidgetManager(Mind *mind)
	: mind_(mind),
	  viewport_(new IsometricPerspective(pixelToMetresScale))
{
	//init Viewport
	viewport_.setMapSize(mind_->getMap()->getSize());

	//init selectionGroups
	for (int i = 0; i < 10; ++i)
		selectionGroups_.insert(i, {});
}

Viewport *GameWidgetManager::viewport()
{
	return &viewport_;
}

void GameWidgetManager::keyPressEvent(const QKeyEvent *event)
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
			if (event->modifiers() & Qt::ControlModifier)
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

void GameWidgetManager::mousePressEvent(const QMouseEvent *event)
{
	QPointF place = viewport_.fromPixelsToMetres(event->pos());
	Object *target = objectInPixelsPos(event->pos());

	//Selection
	if (event->button() == Qt::LeftButton) {
		if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
			if (target != nullptr)
				addUnitsToSelection(fiterSelection({target}));
		}
		else {
			if (target == nullptr)
				selectUnits({});
			else
				selectUnits(fiterSelection({target}));
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
					QPointF pos =
						QPointF(unit->property(TempData::X).toDouble(),
							unit->property(TempData::Y).toDouble());
					unit->setCurrentPath(mind_->getMapManager()->getPath(pos, place));
					unit->setCommand(BS::Command::Move);
				}
				else {
					unit->setTargetObject(target->getUid());
					unit->setCommand(BS::Command::Attack);
				}
			}
		}
	}
}

void GameWidgetManager::gameWidgetResized(QSize sizeInPixels)
{
	viewport_.setViewSizeInPixels(sizeInPixels);
}

void GameWidgetManager::addUnitToSelectionByUid(int uid)
{
	Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (unit == nullptr)
		return;
	addUnitsToSelection({unit});
}

void GameWidgetManager::healUnitByUid(int uid)
{
	Unit *target = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (target == nullptr)
		return;
	for (auto &unit : selectedUnits_) {
		unit->setTargetObject(target->getUid());
		unit->setCommand(BS::Command::Heal);
	}
}

void GameWidgetManager::selectUnitByUid(int uid)
{
	Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (unit == nullptr)
		return;
	selectUnits({unit});
}

void GameWidgetManager::showUnitByUid(int uid)
{
	//TODO conter viewport on unit position
}

Unit *GameWidgetManager::unitByNumber(int number) const
{
	QList<int> allUnits = mind_->getPlayerFaction()->getAllUnits();
	if (number < 1 || number > allUnits.size())
		return nullptr;
	return dynamic_cast<Unit *>(mind_->getObjectFromUid(allUnits[number - 1]));
}

Object *GameWidgetManager::objectInPixelsPos(QPoint pointInPixels) const
{
	QPointF point = viewport_.fromPixelsToMetres(pointInPixels);

	point -= QPointF(0.1, 0.1);
	const QList<const Object *> objects = mind_->physicsEngine()->getObjectsInRect(QRectF(point, QSizeF{0.2, 0.2}));

	if (objects.isEmpty())
		return nullptr;

	return mind_->getObjectFromUid(objects[0]->getUid());
}

QSet<Unit *> GameWidgetManager::fiterSelection(const QSet<Object *> &objects) const
{
	QSet<Unit *> units;
	for (auto &object : objects) {
		Unit *unit = dynamic_cast<Unit *>(object);
		if (unit)
			units.insert(unit);
	}
	return units;
}

void GameWidgetManager::selectUnits(const QSet<Unit *> &units)
{
	for (auto &unit : selectedUnits_)
		unit->property(TempData::IsSelected) = QVariant(false);

	selectedUnits_ = units;

	for (auto &unit : selectedUnits_) {
		unit->property(TempData::IsSelected) = QVariant(true);
		qDebug() << unit->getName();
	}
}

void GameWidgetManager::addUnitsToSelection(QSet<Unit *> units)
{
	selectedUnits_.unite(units);

	for (auto &unit : units) {
		unit->property(TempData::IsSelected) = QVariant(true);
		qDebug() << unit->getName();
	}
}