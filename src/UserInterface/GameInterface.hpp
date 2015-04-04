/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "UserInterface/GameWindows.hpp"
#include "UserInterface/GameViewport.hpp"
#include "UserInterface/GameSelections.hpp"
#include "UserInterface/GameCommands.hpp"
#include "Common/Enums.hpp"

class BoardWidget;
class DataManager;
class FactionPanel;
class Mind;
class UnitsPanel;
class Viewport;

class GameInterface : public QWidget {
	Q_OBJECT
public:
	static const int UpdateTimerInterval; //in milliseconds

	GameInterface(Mind *m, DataManager *dm, BoardWidget *bw, QWidget *parent = nullptr);

	Viewport *viewport();

public slots:
	void startUpdateLoop();

private:
    void initBoardWidget();
	void initUnitsPanel();
	void initFactionPanel();

	void refresh();

	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);


	Mind *const mind_;
	DataManager *const dataManager_;

	BoardWidget *boardWidget_;
	UnitsPanel *unitsPanel_;
	FactionPanel *factionPanel_;

	QTimer *updateTimer_;
	bool isPaused_;

	GameWindows gameWindows_;
	GameViewport gameViewport_;
	GameSelections gameSelections_;
	GameCommands gameCommands_;

private slots:
	void adjustUnitsPanelGeometry();
	void pauseGame();
	void resumeGame();

signals:
	void showMainMenu();
	void gameEnded(BS::GameState gameState);
};
