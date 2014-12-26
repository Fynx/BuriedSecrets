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
	void initLayout();
	void switchToGame();
	void switchToMainMenu();

	//DEV TMP
	void devActionsMenu();

	static const int MainMenuWindowIndex = 0;
	static const int GameWindowIndex = 1;

	General *general;
	Mind *mind;
	InterfaceDataManager *interfaceDataManager;

	QMainWindow *mainWindow;
	QStackedWidget *stackedWidget;
	MainMenuWindow *mainMenuWindow;
	GameWindow *gameWindow;
};
