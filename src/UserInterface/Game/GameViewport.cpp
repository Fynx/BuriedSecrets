/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Game/GameViewport.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/MapManager/MapManager.hpp"
#include "Mind/Mind.hpp"
#include "GameObjects/Unit.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "UserInterface/BoardWidget.hpp"
#include "UserInterface/Viewport/IsometricPerspective.hpp"
#include "Common/Geometry.hpp"
#include "Common/Strings.hpp"
#include "GameObjects/Object.hpp"

const float GameViewport::pixelToMetresScale = 30.0f;
const int GameViewport::ViewportKeyMoveDelta = 300;
const int GameViewport::ViewportEdgeMoveDelta = 15;
const int GameViewport::EdgeViewportMoveTimerInterval = 10;
const qreal GameViewport::ViewportZoomDelta = 0.05f;

GameViewport::GameViewport(Mind *mind, BoardWidget *boardWidget)
	: mind_(mind),
	  boardWidget_(boardWidget),
	  viewport_(new IsometricPerspective(pixelToMetresScale))
{
	//init Viewport
	viewport_.setMapSize(mind_->getMap()->getSize());
	//center on camp
	showObject(mind_->getObjectFromUid(mind_->getPlayerFaction()->getCampUid()));

	connect(&edgeMoveTimer_, &QTimer::timeout, this, &GameViewport::checkForViewportMove);

	edgeMoveTimer_.start(EdgeViewportMoveTimerInterval);
}

const Viewport *GameViewport::viewport() const
{
	return &viewport_;
}

Object *GameViewport::objectInPixelsPos(QPoint pointInPixels) const
{
	QPointF point = viewport_.getPhysicalCoordinates(pointInPixels);

	point -= QPointF(0.1, 0.1);
	auto rect = QRectF(point, QSizeF{0.2, 0.2});
	QList<const Object *> objects = mind_->physicsEngine()->getObjectsInRect(rect);
	objects = filterOutSpam(objects, rect);

	if (objects.isEmpty())
		return nullptr;

	return mind_->getObjectFromUid(objects[0]->getUid());
}

QSet<Object *> GameViewport::objectInPixelsRect(QRect rectInPixels) const
{
	auto topLeftInMetres = viewport_.getPhysicalCoordinates(rectInPixels.topLeft());
	auto botomRightInMetres = viewport_.getPhysicalCoordinates(rectInPixels.bottomRight());
	QRectF rectInMetres(topLeftInMetres, botomRightInMetres);
	rectInMetres = rectInMetres.normalized();

	QList<const Object *> objects = mind_->physicsEngine()->getObjectsInRect(rectInMetres);
	objects = filterOutSpam(objects, rectInMetres);

	QSet<Object *> result;
	for (auto &obj : objects)
		result.insert(mind_->getObjectFromUid(obj->getUid()));

	return result;
}

Viewport *GameViewport::viewport()
{
	return &viewport_;
}

void GameViewport::keyPressEvent(const QKeyEvent *event)
{
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
}

void GameViewport::gameWidgetResized(QSize sizeInPixels)
{
	viewport_.setViewSizeInPixels(sizeInPixels);
}

void GameViewport::showObject(Object *obj)
{
	viewport_.centerOnPointInMetres(mind_->physicsEngine()->getPosition(obj));
}

void GameViewport::showUnit(int uid)
{
	if (!mind_->getPlayerFaction()->isAliveMember(uid))
		return;

	auto unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	auto obj = dynamic_cast<Object *>(unit);

	if (unit->getState() == BS::State::Inside)
		obj = dynamic_cast<Object *>(unit->getLocation());

	showObject(obj);
}

QList<const Object *> GameViewport::filterOutSpam(QList<const Object *> objects, const QRectF &rect) const
{
	QList<const Object *> result;
	for (auto obj : objects) {
		if (! obj->getPrototype()->hasProperty(Properties::BasePolygon)) {
			result.push_back(obj);
			continue;
		}

		//calculate base polygon in metres
		auto polygon = obj->getPrototype()->getBasePolygon();
		auto position = mind_->physicsEngine()->getPosition(obj);
		auto center = obj->getPrototype()->getBaseCentre();
		for (auto &p : polygon)
			p = p - center + position;

		//check if polygon is valid
		if (polygon.isEmpty())
			continue;
		//check if polygon is in rect
		if (rect.contains(polygon[0])) {
			result.push_back(obj);
			continue;
		}
		//check if polygon intersects rect (heuristic)
		QList<QPointF> corners{rect.topLeft(), rect.topRight(), rect.bottomLeft(), rect.bottomRight()};
		for (auto corner : corners) {
			if (BS::Geometry::pointInPolygon(corner, polygon)) {
				result.push_back(obj);
				continue;
			}
		}
	}
	return result;
}

void GameViewport::checkForViewportMove()
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
