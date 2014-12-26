/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class General;
class InterfaceDataManager;

class MainMenuWindow : public QWidget {

Q_OBJECT;
public:
	MainMenuWindow(InterfaceDataManager *dataManager, General *general, QWidget *parent = nullptr);

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

	InterfaceDataManager *dataManager_;
	General *general_;

signals:
	void quit();
	void switchToGame();
};
