/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "UserInterface/Viewport.hpp"

class Mind;
class Object;
class Unit;

class GameWidgetManager : public QObject {
	Q_OBJECT
public:
	static const float pixelToMetresScale; // Number of pixels per meter
	static const int ViewportMoveDelta;
	static const qreal ViewportZoomDelta;

	GameWidgetManager(Mind *mind);

	Viewport *viewport();

	void keyPressEvent(const QKeyEvent *event);
	void mousePressEvent(const QMouseEvent *event);
	void gameWidgetResized(QSize sizeInPixels);

public slots:
	void selectUnit(int uid);

private:
	const QList<Object *> &fiterSelection(const QList<Object *> &objects);
	void selectObjects(const QList<Object *> &objects);

	Mind *mind_;
	Viewport viewport_;
	QList<Object *> selectedObjects_;
};
