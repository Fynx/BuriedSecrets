/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/GameWindow.hpp"

#include "Mind/Mind.hpp"
#include "UserInterface/IsometricPerspective.hpp"
#include "UserInterface/Viewport.hpp"
#include "UserInterface/InterfaceDataManager.hpp"


GameWindow::GameWindow(InterfaceDataManager *dataManager, Mind *mind, QWidget *graphicsWidget, QWidget *parent)
	: QWidget(parent),
	  dataManager_(dataManager),
	  mind_(mind),
	  graphicsWidget_(graphicsWidget),
	  bottomPanel_(new QFrame)
{
	graphicsWidget_->setParent(this);
	bottomPanel_->setParent(this);

	initBottomPanel();
	initViewport();
}

Viewport * GameWindow::viewport()
{
	return viewport_;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) {
		emit showMainMenu();
	}
	else
		QWidget::keyPressEvent(event);
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
	//maximize graphicsWidget_
	graphicsWidget_->setGeometry(0, 0, event->size().width(), event->size().height());

	//resize bottomPanel
	QPoint topLeftCorner = QPoint(event->size().width() - BottomPanelSize.width(),
								  event->size().height() - BottomPanelSize.height());
	bottomPanel_->setGeometry(QRect(topLeftCorner, BottomPanelSize));
	//update viewport
	viewport_->setViewSize(graphicsWidget_->width(), graphicsWidget_->height());

	QWidget::resizeEvent(event);
}

void GameWindow::initBottomPanel()
{
	QHBoxLayout *BPLayout = new QHBoxLayout;
	bottomPanel_->setLayout(BPLayout);

	const QIcon *journalIcon = dataManager_->getIcon("journal");
	QPushButton *journalBtn = new QPushButton(*journalIcon, "Journal");
	journalBtn->setIconSize(BottomPanelIconsSize);
	journalBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	BPLayout->addWidget(journalBtn);

	const QIcon *campEQIcon = dataManager_->getIcon("campEQ");
	QPushButton *campEQBtn = new QPushButton(*campEQIcon, "Camp EQ");
	campEQBtn->setIconSize(BottomPanelIconsSize);
	campEQBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	BPLayout->addWidget(campEQBtn);
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
