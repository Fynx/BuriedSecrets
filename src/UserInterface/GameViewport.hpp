/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "UserInterface/Viewport.hpp"

class BoardWidget;
class Mind;
class Object;

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
	void showUnit(int uid);

private:
	Mind *const mind_;
	BoardWidget *boardWidget_;
	Viewport viewport_;
	QTimer *edgeMoveTimer_;

private slots:
	void checkForViewportMove();
};
