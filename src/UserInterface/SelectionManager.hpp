/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "UserInterface/Viewport.hpp"

class Effect;
class Mind;
class Object;
class Unit;
class Location;

class SelectionManager : public QObject {
	Q_OBJECT
public:
	static const float pixelToMetresScale; // Number of pixels per meter
	static const int ViewportMoveDelta;
	static const qreal ViewportZoomDelta;
	static const QColor SelectionColor;

	SelectionManager(Mind *mind);

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
	void makePrimaryAction(Unit *unit, QPointF point, Object *target);
	void makeSecondaryAction(Unit *unit, QPointF point, Object *target);
	bool isFriendly(Object *object);

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

	Mind *const mind_;
	Viewport viewport_;

	QSet<int> selectedUnitsUids_;
	int selectedLocationUid_;
	QMap<int, QSet<int>> selectionGroupsUids_;

	QHash<int, QLinkedList<Effect>::iterator> uidToSelectionEffect_;
};
