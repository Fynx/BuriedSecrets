/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/GameWindow.hpp"

GameWindow::GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent)
	: QWidget(parent), mind(mind), graphicsWidget(graphicsWidget)
{
	graphicsWidget->setParent(this);
}


void GameWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) {
		emit switchToMainMenu();
	}
	else
		QWidget::keyPressEvent(event);
}


void GameWindow::resizeEvent(QResizeEvent *event)
{
	//maximize graphicsWidget
	graphicsWidget->setGeometry(0, 0, event->size().width(), event->size().height());

	QWidget::resizeEvent(event);
}
