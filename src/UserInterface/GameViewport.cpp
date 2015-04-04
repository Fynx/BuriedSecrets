/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "GameViewport.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/BoardWidget.hpp"
#include "UserInterface/IsometricPerspective.hpp"

const float GameViewport::pixelToMetresScale = 30.0f;
const int GameViewport::ViewportKeyMoveDelta = 300;
const int GameViewport::ViewportEdgeMoveDelta = 15;
const int GameViewport::EdgeViewportMoveTimerInterval = 10;
const qreal GameViewport::ViewportZoomDelta = 0.05f;

GameViewport::GameViewport(Mind *mind, BoardWidget *boardWidget)
	: mind_(mind),
	  boardWidget_(boardWidget),
	  viewport_(new IsometricPerspective(pixelToMetresScale)),
	  edgeMoveTimer_(new QTimer)
{
	//init Viewport
	viewport_.setMapSize(mind_->getMap()->getSize());
	auto campPos = mind_->physicsEngine()->getPosition(mind_->getObjectFromUid(mind_->getPlayerFaction()->getCampUid()));
	viewport_.centerOnPointInMetres(campPos);

	connect(edgeMoveTimer_, &QTimer::timeout, this, &GameViewport::checkForViewportMove);

	edgeMoveTimer_->start(EdgeViewportMoveTimerInterval);
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

Object *GameViewport::objectInPixelsPos(QPoint pointInPixels) const
{
	QPointF point = viewport_.getPhysicalCoordinates(pointInPixels);

	point -= QPointF(0.1, 0.1);
	QList<const Object *> objects = mind_->physicsEngine()->getObjectsInRect(QRectF(point, QSizeF{0.2, 0.2}));

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

	QSet<Object *> result;
	for (auto &obj : objects)
		result.insert(mind_->getObjectFromUid(obj->getUid()));

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
