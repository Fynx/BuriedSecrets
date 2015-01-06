/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/GameWindow.hpp"

#include "Mind/Mind.hpp"
#include "UserInterface/IsometricPerspective.hpp"
#include "UserInterface/Viewport.hpp"
#include "UserInterface/UnitsPanel.hpp"


GameWindow::GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent)
	: QWidget(parent),
	  mind_(mind),
	  viewport_(nullptr),
	  graphicsWidget_(graphicsWidget),
	  unitsPanel_(new UnitsPanel),
	  bottomPanel_(new QFrame)
{
	graphicsWidget_->setParent(this);
	bottomPanel_->setParent(this);
	unitsPanel_->setParent(this);

	graphicsWidget_->lower();

	initBottomPanel();
	initViewport();
}

GameWindow::~GameWindow()
{
	delete viewport_;
}

Viewport * GameWindow::viewport()
{
	return viewport_;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_Escape:
			emit showMainMenu();
			break;
		case Qt::Key_W:
			viewport_->moveViewInPixels(QPointF{0, ViewportMoveDelta});
			break;
		case Qt::Key_S:
			viewport_->moveViewInPixels(QPointF{0, ViewportMoveDelta * (-1)});
			break;
		case Qt::Key_A:
			viewport_->moveViewInPixels(QPointF{ViewportMoveDelta * (-1), 0});
			break;
		case Qt::Key_D:
			viewport_->moveViewInPixels(QPointF{ViewportMoveDelta, 0});
			break;
		case Qt::Key_Plus:
			viewport_->zoomIn(ViewportZoomDelta);
			break;
		case Qt::Key_Minus:
			viewport_->zoomIn(ViewportZoomDelta * (-1));
			break;
		case Qt::Key_0:
			viewport_->resetZoom();
			break;
		default:
			QWidget::keyPressEvent(event);
	}
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
	QPoint topLeft;
	//maximize graphicsWidget_
	graphicsWidget_->setGeometry(0, 0, event->size().width(), event->size().height());

	//resize unitsPanel
	topLeft = QPoint((event->size().width() - unitsPanel_->sizeHint().width()) / 2, 0);
	unitsPanel_->setGeometry(QRect(topLeft, unitsPanel_->sizeHint()));
	qDebug() << unitsPanel_->sizeHint();

	//resize bottomPanel
	topLeft = QPoint(event->size().width() - BottomPanelSize.width(),
	                 event->size().height() - BottomPanelSize.height());
	bottomPanel_->setGeometry(QRect(topLeft, BottomPanelSize));

	//resize viewport
	viewport_->setViewSizeInPixels(QSizeF(event->size().width(), event->size().height()));
	qDebug() << viewport_->toString();

	QWidget::resizeEvent(event);
}

void GameWindow::initBottomPanel()
{
	bottomPanel_->setAutoFillBackground(true);

	bottomPanel_->setLayout(new QHBoxLayout);

	QPushButton *journalBtn = new QPushButton("Journal");
	journalBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	bottomPanel_->layout()->addWidget(journalBtn);

	QPushButton *campEQBtn = new QPushButton("Camp EQ");
	campEQBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	bottomPanel_->layout()->addWidget(campEQBtn);
}

void GameWindow::initViewport()
{
	// Number of pixels per meter
	const float metreToPxScale = 30.0f;
	// TODO after MapManager is added and there is some map passed to UI, we will need to get the real size here.
	// For now:
	const float mapWidth = 500;
	const float mapHeight = 500;
	viewport_ = new Viewport(new IsometricPerspective(metreToPxScale));
	viewport_->setMapSize(mapWidth, mapHeight);
}
