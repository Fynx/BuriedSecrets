/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "UserInterface/Viewport.hpp"

class Mind;
class Object;
class Unit;
class Building;

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

	void refresh();

public slots:
	void addUnitToSelectionByUid(int uid);
	void healUnitByUid(int uid);
	void selectUnitByUid(int uid);
	void showUnitByUid(int uid);

private:
	Unit *unitByNumber(int number) const;
	Object *objectInPixelsPos(QPoint pointInPixels) const;
	QSet<Unit *> fiterSelection(const QSet<Object *> &objects) const;
	void selectUnits(const QSet<Unit *> &units);
	void addUnitsToSelection(QSet<Unit *> units);
	void markBuildingsSelected();

	bool isPaused_;
	Mind *mind_;
	Viewport viewport_;
	QSet<Unit *> selectedUnits_;
	QSet<Building *> selectedBuildings_;
	QMap<int, QSet<Unit *>> selectionGroups_;
};
