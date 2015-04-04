/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class BoardWidget;
class Effect;
class GameViewport;
class Mind;
class Object;
class Unit;

class GameSelections : public QObject {
	Q_OBJECT
public:
	GameSelections(Mind *m, const GameViewport &gv);

	const QSet<int> &selectedUnitsUids() const;

	void keyPressEvent(const QKeyEvent *event);
	void mousePressEvent(const QMouseEvent *event);
	void refresh();

public slots:
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
	const GameViewport &gameViewport_;

	QSet<int> selectedUnitsUids_;
	int selectedLocationUid_;
	QMap<int, QSet<int>> selectionGroupsUids_;

	QHash<int, QLinkedList<Effect>::iterator> uidToSelectionEffect_;

signals:
	void selectionChanged(int uid, bool isSelected);
};
