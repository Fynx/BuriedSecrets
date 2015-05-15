/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "UserInterface/Viewport/Viewport.hpp"

class BoardWidget;
class Mind;
class Object;

/**
 * UI game module to control current viewport and its movement.
 * Can tell what units are in specific area.
 * Can center on specific unit.
 */
class GameViewport : public QObject {
	Q_OBJECT
public:
	static const float pixelToMetresScale; // Number of pixels per meter
	static const int ViewportKeyMoveDelta;
	static const int ViewportEdgeMoveDelta;
	static const int EdgeViewportMoveTimerInterval;
	static const qreal ViewportZoomDelta;

	GameViewport(Mind *mind, BoardWidget *boardWidget);

	const Viewport *viewport() const;
	Object *objectInPixelsPos(QPoint pointInPixels) const;
	QSet<Object *> objectInPixelsRect(QRect rectInPixels) const;

	Viewport *viewport();

	void keyPressEvent(const QKeyEvent *event);
	void gameWidgetResized(QSize sizeInPixels);

	void showObject(Object *obj);

public slots:
	void showUnit(int uid);

private:
	QList<const Object *> filterOutSpam(QList<const Object *> objects, const QRectF &rect) const;

	Mind *const mind_;
	BoardWidget *boardWidget_;
	Viewport viewport_;
	QTimer edgeMoveTimer_;

private slots:
	void checkForViewportMove();
};
