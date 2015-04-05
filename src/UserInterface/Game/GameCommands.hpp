/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "Common/Enums.hpp"

class BoardWidget;
class Effect;
class Mind;
class Object;
class Unit;
class GameViewport;
class GameSelections;

class GameCommands : public QObject {
	Q_OBJECT
public:
	GameCommands(Mind *m, BoardWidget *bw, const GameViewport &gv, const GameSelections &gs);

	void mousePressEvent(const QMouseEvent *event);
	void refresh();

private:
	const QSet<int> &selectedUnits();

	BS::Command choosePrimaryCommand(Unit *unit, Object *target);
	BS::Command chooseSecondaryCommand(Unit *unit, Object *target);
	void instructCommand(BS::Command command, Unit *unit, QPointF point, Object *target);

	void adjustCursor();
	void checkForMoveCommand();
	void checkForBaseVisit();

	Mind *const mind_;
	BoardWidget *boardWidget_;
	const GameViewport &gameViewport_;
	const GameSelections &gameSelections_;
	bool isVisiting_;

signals:
	void visitBase(Unit *unit);
};
