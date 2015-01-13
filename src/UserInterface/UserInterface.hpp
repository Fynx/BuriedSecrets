/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class General;
class Mind;
class InterfaceDataManager;
class Viewport;
class MainMenuWindow;
class GameWindow;

class UserInterface : public QObject {
	Q_OBJECT
public:
	UserInterface(General *general);
	~UserInterface();

	QMainWindow *getMainWindow();
	Viewport *getViewport(); //TODO see if not const

	bool gameInProgress() const;
	void clearGame();
	void newGame(Mind *mind, QWidget *graphicsWidget);

private:
	enum class Window : quint8 {
		MainMenu,
		Game,
		LoadGame,
		SaveGame,
		Instructions
};

	General *general_;

	QMainWindow *mainWindow_;
	GameWindow *gameWindow_;
	MainMenuWindow *mainMenuWindow_;
	QStackedWidget *stackedWidget_;

	void initLayout();
	void initWindows();
	void switchToWindow(Window window);

	//DEV TMP
	void initDevActionsMenu();
	QAction *actionUILoop_;

private slots:
	void onShowMainMenu();
	void onNewGame();
	void onContinueGame();
};
