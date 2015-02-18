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

class SelectionManager : public QObject {
	Q_OBJECT
public:
	static const float pixelToMetresScale; // Number of pixels per meter
	static const int ViewportMoveDelta;
	static const qreal ViewportZoomDelta;

	SelectionManager(Mind *mind);

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
	void selectionByRectEnded(const QRect &selectionRect);

private:
	Unit *unitByNumber(int number) const;
	Object *objectInPixelsPos(QPoint pointInPixels) const;
	QSet<Object *> objectInPixelsRect(QRect rectInPixels) const;
	QSet<Unit *> filterSelection(const QSet<Object *> &objects) const;
	void selectUnits(const QSet<Unit *> &units);
	void addUnitsToSelection(QSet<Unit *> units);
	void markBuildingsSelected();

	Mind *mind_;
	Viewport viewport_;

	bool isRubberBandVisible_;
	QRect rubberBandRectInMetres_;

	QSet<Unit *> selectedUnits_;
	QSet<Building *> selectedBuildings_;
	QMap<int, QSet<Unit *>> selectionGroups_;
};
