/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

class General;
class DataManager;

#include <QtWidgets>

class MainMenuWindow : public QWidget {

Q_OBJECT;
public:
	MainMenuWindow(DataManager *dataManager, General *general, QWidget *parent = nullptr);

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

	QPushButton *continueBtn_;
	QPushButton *newGameBtn_;
	QPushButton *loadGameBtn_;
	QPushButton *saveGameBtn_;
	QPushButton *instructionsBtn_;
	QPushButton *quitGameBtn_;

	QStackedWidget *stackedWidget_;
	bool gameInProgress_;

	DataManager *dataManager_;
	General *general_;

signals:
	void quit();
	void switchToGame();
};
