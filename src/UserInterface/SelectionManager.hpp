/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "UserInterface/Viewport.hpp"
#include "Common/Enums.hpp"

class BoardWidget;
class Effect;
class Mind;
class Object;
class Unit;
class Location;

class SelectionManager : public QObject {
	Q_OBJECT
public:
	static const float pixelToMetresScale; // Number of pixels per meter
	static const int ViewportKeyMoveDelta;
	static const int ViewportEdgeMoveDelta;
	static const int EdgeViewportMoveTimerInterval;
	static const qreal ViewportZoomDelta;
	static const QColor SelectionColor;

	SelectionManager(Mind *mind, BoardWidget *boardWidget);

	Viewport *viewport();

	void keyPressEvent(const QKeyEvent *event);
	void mousePressEvent(const QMouseEvent *event);
	void gameWidgetResized(QSize sizeInPixels);

	void refresh();

public slots:
	void showUnit(int uid);
	void pickUnit(int uid);
	void selectionByRectEnded(const QRect &selectionRect);

private:
	BS::Command choosePrimaryCommand(Unit *unit, Object *target);
	BS::Command chooseSecondaryCommand(Unit *unit, Object *target);
	void instructCommand(BS::Command command, Unit *unit, QPointF point, Object *target);

	int unitNumberToUid(int number) const;
	Object *objectInPixelsPos(QPoint pointInPixels) const;
	QSet<Object *> objectInPixelsRect(QRect rectInPixels) const;

	QSet<int> filterSelection(const QSet<Object *> &objects) const;
	void selectUnits(const QSet<int> &unitsUids);
	void addUnitsToSelection(QSet<int> unitsUids);
	void markBuildingsSelected();
	void addSelectionEffect(int objUid);
	void removeSelectionEffect(int objUid);
	void removeDeadFromSelection();
	void adjustCursor();
	void checkForMoveCommand();

	Mind *const mind_;
	BoardWidget *boardWidget_;
	Viewport viewport_;
	QTimer *edgeMoveTimer_;

	QSet<int> selectedUnitsUids_;
	int selectedLocationUid_;
	QMap<int, QSet<int>> selectionGroupsUids_;

	QHash<int, QLinkedList<Effect>::iterator> uidToSelectionEffect_;

private slots:
	void checkForViewportMove();
};
