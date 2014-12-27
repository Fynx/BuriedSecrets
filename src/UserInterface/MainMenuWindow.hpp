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
	MainMenuWindow(InterfaceDataManager *dataManager, QWidget *parent = nullptr);

private:
	void initButtons();
	void initLayout();


	QPushButton *continueBtn_;
	QPushButton *newGameBtn_;
	QPushButton *loadGameBtn_;
	QPushButton *saveGameBtn_;
	QPushButton *instructionsBtn_;
	QPushButton *quitGameBtn_;

	QStackedWidget *stackedWidget_;
	bool gameInProgress_;

	InterfaceDataManager *dataManager_;

private slots:
	void adjustButtonsVisibility();

signals:
	void continueActivated();
	void newGameActivated();
	void loadGameActivated();
	void saveGameActivated();
	void instructionsActivated();
	void quitActivated();
};
