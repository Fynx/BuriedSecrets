/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtWidgets>

#include "Graphics/GraphicsWidget.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/MainMenuWindow.hpp"
#include "UserInterface/GameWindow.hpp"
#include "UserInterface/Viewport.hpp"


// Forward declaration.
class General;


class UserInterface : public QObject {

Q_OBJECT;
public:
	UserInterface(General *general, Mind *mind, QWidget *graphicsWidget);
	~UserInterface();

	QMainWindow *getMainWindow();
	Viewport *getViewport();

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

	General  *general;
	Mind        *mind;

	Viewport *viewport;
};
