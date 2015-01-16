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
	viewport_.setMapSize(mind_->getMap()->getSize());
}

Viewport *GameWidgetManager::viewport()
{
	return &viewport_;
}

void GameWidgetManager::keyPressEvent(const QKeyEvent *event)
{
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
		case Qt::Key_0:
			viewport_.resetZoom();
			break;
	}
}

void GameWidgetManager::mousePressEvent(const QMouseEvent *event)
{
	QPointF point = viewport_.fromPixelsToMetres(event->pos());

	if (event->button() == Qt::LeftButton) {
		point -= QPointF(0.1, 0.1);
		const QList<const Object *> objects = mind_->physicsEngine()->getObjectsInRect(QRectF(point, QSizeF{0.2, 0.2}));

		if (objects.isEmpty()) {
			selectObjects({});
			return;
		}

		Object *object = mind_->getObjectFromUid(objects[0]->getUid());
		selectObjects(fiterSelection({object}));
		return;
	}
	if (event->button() == Qt::RightButton) {
		for (auto &object : selectedObjects_) {
			if (object->getType() == BS::Type::Unit) {
				Unit* unit = static_cast<Unit *>(object);
				unit->setCommand(BS::Command::Move);

				QPointF pos = QPointF(unit->property(Properties::X).toDouble(), unit->property(Properties::Y).toDouble());
				unit->setCurrentPath(mind_->getMapManager()->getPath(pos, point));
				qDebug() << "Move" << unit->getName() << "to" << point;
			}
		}
		return;
	}
}

void GameWidgetManager::gameWidgetResized(QSize sizeInPixels)
{
	viewport_.setViewSizeInPixels(sizeInPixels);
}

void GameWidgetManager::selectUnit(int uid)
{
	selectObjects({mind_->getObjectFromUid(uid)});
}

const QList<Object *> &GameWidgetManager::fiterSelection(const QList<Object *> &objects)
{
	//TODO
	return objects;
}

void GameWidgetManager::selectObjects(const QList<Object *> &objects)
{
	for (auto &object : selectedObjects_)
		object->property(Properties::IsSelected) = QVariant(false);

	selectedObjects_ = objects;

	for (auto &object : selectedObjects_) {
		object->property(Properties::IsSelected) = QVariant(true);
		qDebug() << object->getName();
	}
}
