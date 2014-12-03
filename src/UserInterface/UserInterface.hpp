/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Graphics/GraphicsWidget.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/MainMenuWindow.hpp"
#include "UserInterface/GameWindow.hpp"

#include <QtWidgets>

// Nah, not a QObject, just for now
class MapManager : public QObject {
Q_OBJECT;
public:
	virtual void loadMap() = 0;
	virtual void saveMap() = 0;

	//...
};

class UserInterface : public QObject {

Q_OBJECT;
public:
	UserInterface(MapManager *mapManager, Mind *mind, QWidget *graphicsWidget);
	~UserInterface();

	QMainWindow *getMainWindow();

private:
	void initLayout();
	void switchToGame();
	void switchToMainMenu();

	static const int MainMenuWindowIndex   = 0;
	static const int GameWindowIndex = 1;

	QMainWindow *mainWindow;
	QStackedWidget *stackedWidget;
	MainMenuWindow *mainMenuWindow;
	GameWindow *gameWindow;

	MapManager  *mapManager;
	Mind        *mind;
};
