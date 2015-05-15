/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "UserInterface/Game/GameWindows.hpp"
#include "UserInterface/Game/GameViewport.hpp"
#include "UserInterface/Game/GameSelections.hpp"
#include "UserInterface/Game/GameCommands.hpp"
#include "Common/Enums.hpp"

class AttitudeWidget;
class BoardWidget;
class DataManager;
class FactionPanel;
class Mind;
class NotificationPanel;
class UnitsPanel;
class Viewport;

/**
 * Class responsible for game window.
 * Contains UI update timer, filters and directs Qt events, checks game state.
 * Parent to all HUD widgets and map.
 * Has all others game modules.
 */
class GameInterface : public QWidget {
	Q_OBJECT
public:
	static const int UpdateTimerInterval; //in milliseconds

	GameInterface(Mind *m, DataManager *dm, BoardWidget *bw, QWidget *parent = nullptr);
    virtual ~GameInterface();

	Viewport *viewport();

public slots:
	void start();

private:
    void initBoardWidget();
	void initAttitudeWidget();
	void initUnitsPanel();
	void initFactionPanel();
	void initNotificationPanel();

	void refresh();

	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);

	Mind *const mind_;
	DataManager *const dataManager_;

	AttitudeWidget *attitudeWidget_;
	BoardWidget *boardWidget_;
	UnitsPanel *unitsPanel_;
	FactionPanel *factionPanel_;
	NotificationPanel *notificationPanel_;

	QTimer updateTimer_;
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
