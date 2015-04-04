/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "UserInterface/GameViewport.hpp"
#include "UserInterface/GameCommands.hpp"
#include "Common/Enums.hpp"

class BoardWidget;
class Effect;
class Mind;
class Object;
class Unit;

class GameSelections : public QObject {
	Q_OBJECT
public:
	GameSelections(Mind *mind, BoardWidget *boardWidget);

	const QSet<int> &selectedUnitsUids() const;

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
	int unitNumberToUid(int number) const;

	QSet<int> filterSelection(const QSet<Object *> &objects) const;
	void selectUnits(const QSet<int> &unitsUids);
	void addUnitsToSelection(QSet<int> unitsUids);
	void markBuildingsSelected();
	void addSelectionEffect(int objUid);
	void removeSelectionEffect(int objUid);
	void removeDeadFromSelection();

	Mind *const mind_;
	GameViewport gameViewport_;
	GameCommands gameCommands_;

	QSet<int> selectedUnitsUids_;
	int selectedLocationUid_;
	QMap<int, QSet<int>> selectionGroupsUids_;

	QHash<int, QLinkedList<Effect>::iterator> uidToSelectionEffect_;

};
