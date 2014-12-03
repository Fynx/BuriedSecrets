/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Mind.hpp"

#include <QtWidgets>

class GameWindow : public QWidget {

Q_OBJECT;
public:
	GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent = nullptr);

private:
	void keyPressEvent(QKeyEvent *event);

	Mind *mind;
	QWidget *graphicsWidget;
	QWidget *minimap;

signals:
	void switchToMainMenu();
};