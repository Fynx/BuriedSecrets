/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/GameWindow.hpp"

GameWindow::GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent)
	: QWidget(parent), mind(mind), graphicsWidget(graphicsWidget), minimap(new QPushButton(this))
{
	graphicsWidget->setParent(this);

	//TODO still temporary
	graphicsWidget->resize(800, 600);
	minimap->raise();
	minimap->resize(150, 200);
	minimap->move(650, 400);
}

void GameWindow::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape) {
		emit switchToMainMenu();
	}
	else
		QWidget::keyPressEvent(event);
}

