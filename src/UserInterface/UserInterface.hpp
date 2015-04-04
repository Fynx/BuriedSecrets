/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "Common/Enums.hpp"

class BoardWidget;
class DataManager;
class General;
class Mind;
class InterfaceDataManager;
class Viewport;
class MainMenuWindow;
class GameInterface;
class PostGameWindow;

class UserInterface : public QObject {
	Q_OBJECT
public:
	UserInterface(General *general, DataManager *dataManager);
	~UserInterface();

	QMainWindow *getMainWindow();
	Viewport *getViewport(); //TODO see if not const

	bool gameInProgress() const;
	void clearGame();
	void newGame(Mind *mind, BoardWidget *boardWidget);

private:
	enum class Window : quint8 {
		MainMenu,
		Game,
		PostGameMenu,
		LoadGame,
		SaveGame,
		Instructions
};

	General *const general_;
	DataManager *const dataManager_;

	QMainWindow *mainWindow_;
	GameInterface *gameWindow_;
	PostGameWindow *postGameWindow_;
	MainMenuWindow *mainMenuWindow_;
	QStackedWidget *stackedWidget_;

	void initLayout();
	void initWindows();
	void switchToWindow(Window window);

	//DEV TMP
	void initDevActionsMenu();
	bool gameEnded_;

private slots:
	void onShowMainMenu();
	void onGameEnded(BS::GameState gs);
	void onAfterGame();
	void onNewGame();
	void onContinueGame();
};
