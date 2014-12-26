/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/GameWindow.hpp"

#include "UserInterface/IsometricPerspective.hpp"

GameWindow::GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent)
	: QWidget(parent), mind_(mind), graphicsWidget_(graphicsWidget)
{
	graphicsWidget_->setParent(this);

	initViewport();
}


Viewport * GameWindow::viewport()
{
	return viewport_;
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
	//maximize graphicsWidget_
	graphicsWidget_->setGeometry(0, 0, event->size().width(), event->size().height());

	//update viewport
	viewport_->setViewSize(graphicsWidget_->width(), graphicsWidget_->height());

	QWidget::resizeEvent(event);
}

void GameWindow::initViewport()
{
	const float metreToPxScale = 30.0f;
	// TODO after MapManager is added and there is some map passed to UI, we will need to get the real size here.
	// For now:
	const float mapWidth = 500;
	const float mapHeight = 500;
	viewport_ = new Viewport(new IsometricPerspective(metreToPxScale));
	viewport_->setMapSize(mapWidth, mapHeight);
}
