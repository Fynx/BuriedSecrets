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
class MainMenu;
class LoadGameMenu;
class SaveGameMenu;
class GameInterface;
class PostGameMenu;

/**
 * Main User Interface module class to manage outside game menus and start / clear game.
 */
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
	enum class Menu : quint8 {
		MainMenu,
		PostGameMenu,
		LoadGameMenu,
		SaveGameMenu,
		Game,
};

	General *const general_;
	DataManager *const dataManager_;

	QMainWindow *mainWindow_;
	GameInterface *gameInterface_;
	PostGameMenu *postGameMenu_;
	MainMenu *mainMenu_;
	LoadGameMenu *loadGameMenu_;
	SaveGameMenu *saveGameMenu_;
	QStackedWidget *stackedWidget_;

	void initLayout();
	void initMenus();
	void switchToMenu(Menu menu);

	//DEV TMP
	void initDevActionsMenu();

private slots:
	void onShowMainMenu();
	void onGameEnded(BS::GameState gs);
	void onAfterGame();
	void onNewGame();
	void onContinueGame();
	void onShowLoadGame();
	void onShowSaveGame();
	void loadGame(QString path);
	void saveGame(QString path);
};
