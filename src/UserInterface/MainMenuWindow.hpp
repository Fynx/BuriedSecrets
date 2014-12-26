/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

class General;

#include <QtWidgets>

class MainMenuWindow : public QWidget {

Q_OBJECT;
public:
	MainMenuWindow(General *general, QWidget *parent = nullptr);

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
	bool gameInProgress;

	General *general;

signals:
	void quit();
	void switchToGame();
};
