/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class General;
class UserInterface;

class MainMenuWindow : public QWidget {
	Q_OBJECT
public:
	MainMenuWindow(const UserInterface *userInterface, QWidget *parent = nullptr);

public slots:
	void adjustButtonsVisibility();

private:
	void keyPressEvent(QKeyEvent *event);

	void initButtons();
	void initLayout();


	QPushButton *continueBtn_;
	QPushButton *newGameBtn_;
	QPushButton *loadGameBtn_;
	QPushButton *saveGameBtn_;
	QPushButton *instructionsBtn_;
	QPushButton *quitGameBtn_;

	QStackedWidget *stackedWidget_;
	const UserInterface *userInterface_;

signals:
	void continueActivated();
	void newGameActivated();
	void loadGameActivated();
	void saveGameActivated();
	void instructionsActivated();
	void quitActivated();
};
