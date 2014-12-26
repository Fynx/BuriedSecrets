/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Mind.hpp"
#include "UserInterface/Viewport.hpp"

#include <QtWidgets>

class GameWindow : public QWidget {
	Q_OBJECT;
public:
	GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent = nullptr);

	Viewport *viewport();

private:
	void keyPressEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent *event);

	void initViewport();

	Mind *mind_;

	Viewport *viewport_;
	QWidget *graphicsWidget_;

signals:
	void switchToMainMenu();
};
