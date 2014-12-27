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

Q_OBJECT;
public:
	UserInterface(const DataManager *dataManager, General *general, Mind *mind, QWidget *graphicsWidget);
	~UserInterface();

	QMainWindow *getMainWindow();
	Viewport *getViewport();

private:
	enum class Window : quint8 {
		MainMenu,
		Game,
		LoadGame,
		SaveGame,
		Instructions
	};


	General *general;
	Mind *mind;
	InterfaceDataManager *interfaceDataManager;

	QMainWindow *mainWindow;
	QStackedWidget *stackedWidget;
	MainMenuWindow *mainMenuWindow;
	GameWindow *gameWindow;

	void initLayout();
	void initWindows();
	void switchToWindow(Window window);

	//DEV TMP
	void initDevActionsMenu();

private slots:
	void onShowMainMenu();
	void onNewGame();
	void onContinueGame();
};
