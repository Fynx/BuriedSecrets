/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Mind.hpp"

#include <QtWidgets>

class MainMenuWindow : public QWidget {

Q_OBJECT;
public:
	MainMenuWindow(Mind *mind, QWidget *parent = nullptr);

private:
	void initButtons();
	void initLayout();
	void adjustButtonsVisibility();

	void onContinueActivated();
	void onNewGameActivated();
	void onLoadGameActivated();
	void onSaveGameActivated();
	void onInstructionsActivated();
	void onQuitActivated();

	QPushButton *continueBtn;
	QPushButton *newGameBtn;
	QPushButton *loadGameBtn;
	QPushButton *saveGameBtn;
	QPushButton *instructionsBtn;
	QPushButton *quitGameBtn;

	QStackedWidget *stackedWidget;
	Mind *mind;
	bool gameInProgress;

signals:
	void quit();
	void switchToGame();
};
