/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class General;
class UserInterface;

/**
 * UI main menu, first thing to display after launch.
 */
class MainMenu : public QWidget {
	Q_OBJECT
public:
	MainMenu(const UserInterface *userInterface, QWidget *parent = nullptr);

public slots:
	void adjustButtonsVisibility();

private:
	static const QMargins ContentsMargins;
	static const int Spacing;

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
