/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/GameWindow.hpp"

#include "Mind/Mind.hpp"
#include "UserInterface/IsometricPerspective.hpp"
#include "UserInterface/Viewport.hpp"
#include "UserInterface/UnitsPanel.hpp"
#include "UserInterface/CampEquipmentWindow.hpp"
#include "UserInterface/JournalWindow.hpp"

GameWindow::GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent)
	: QWidget(parent),
	  mind_(mind),
	  viewport_(nullptr),
	  graphicsWidget_(graphicsWidget),
	  unitsPanel_(new UnitsPanel),
	  bottomPanel_(new QFrame),
	  campEquipmentWindow_(new CampEquipmentWindow),
	  journalWindow_(new JournalWindow)
{
	graphicsWidget_->setParent(this);
	bottomPanel_->setParent(this);
	unitsPanel_->setParent(this);
	campEquipmentWindow_->setParent(this);
	journalWindow_->setParent(this);

	initBottomPanel();
	initCampEquipmentWidget();
	initJournal();
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
	QSize widgetSize;

	//maximize graphicsWidget_
	graphicsWidget_->setGeometry(0, 0, event->size().width(), event->size().height());

	//resize unitsPanel
	topLeft = QPoint((event->size().width() - unitsPanel_->sizeHint().width()) / 2, 0);
	unitsPanel_->setGeometry(QRect(topLeft, unitsPanel_->sizeHint()));

	//resize bottomPanel
	topLeft = QPoint(event->size().width() - BottomPanelSize.width(),
	                 event->size().height() - BottomPanelSize.height());
	bottomPanel_->setGeometry(QRect(topLeft, BottomPanelSize));

	//set size of campEquipmentWindow
	topLeft = QPoint(0, unitsPanel_->sizeHint().height());
	widgetSize = QSize(event->size().width() / 2, event->size().height() - topLeft.y());
	campEquipmentWindow_->setGeometry(QRect(topLeft, widgetSize));
	//set size of journalWindow
	journalWindow_->setGeometry(QRect(topLeft, widgetSize));

	//set size of viewport
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
	connect(journalBtn, &QPushButton::clicked, journalWindow_, &JournalWindow::show);
	connect(journalBtn, &QPushButton::clicked, campEquipmentWindow_, &CampEquipmentWindow::hide);

	QPushButton *campEQBtn = new QPushButton("Camp EQ");
	campEQBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	bottomPanel_->layout()->addWidget(campEQBtn);
	connect(campEQBtn, &QPushButton::clicked, campEquipmentWindow_, &CampEquipmentWindow::show);
	connect(campEQBtn, &QPushButton::clicked, journalWindow_, &JournalWindow::hide);
}

void GameWindow::initCampEquipmentWidget()
{
	campEquipmentWindow_->hide();
}

void GameWindow::initJournal()
{
	journalWindow_->hide();
}

void GameWindow::initViewport()
{
	// Number of pixels per meter
	const float pixelToMetresScale = 30.0f;
	// TODO after MapManager is added and there is some map passed to UI, we will need to get the real size here.
	// For now:
	const float mapWidth = 500;
	const float mapHeight = 500;
	viewport_ = new Viewport(new IsometricPerspective(pixelToMetresScale));
	viewport_->setMapSize(mapWidth, mapHeight);
}
