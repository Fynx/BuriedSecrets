/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/GameWindow.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"
#include "Common/Strings.hpp"
#include "UserInterface/IsometricPerspective.hpp"
#include "UserInterface/Viewport.hpp"
#include "UserInterface/UnitsPanel.hpp"
#include "UserInterface/CampPanel.hpp"
#include "UserInterface/CampEquipmentWindow.hpp"
#include "UserInterface/JournalWindow.hpp"

GameWindow::GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent)
	: QWidget(parent),
	  mind_(mind),
	  viewport_(nullptr),
	  graphicsWidget_(graphicsWidget),
	  unitsPanel_(new UnitsPanel),
	  campPanel_(new CampPanel),
	  campEquipmentWindow_(new CampEquipmentWindow),
	  journalWindow_(new JournalWindow),
	  updateTimer_(new QTimer)
{
	graphicsWidget_->setParent(this);
	campPanel_->setParent(this);
	unitsPanel_->setParent(this);
	campEquipmentWindow_->setParent(this);
	journalWindow_->setParent(this);

	connect(campPanel_, &CampPanel::journalActivated, journalWindow_, &JournalWindow::show);
	connect(campPanel_, &CampPanel::journalActivated, campEquipmentWindow_, &CampEquipmentWindow::hide);
	connect(campPanel_, &CampPanel::campEQActivated, campEquipmentWindow_, &CampEquipmentWindow::show);
	connect(campPanel_, &CampPanel::campEQActivated, journalWindow_, &JournalWindow::hide);

	connect(updateTimer_, &QTimer::timeout, this, &GameWindow::update);

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

void GameWindow::startUpdateLoop()
{
	info("Starting UI update loop.");

	update();
	updateTimer_->start(UpdateTimerInterval);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_Escape:
			emit showMainMenu();
			break;
		case Qt::Key_W:
			viewport_->moveViewInPixels(QPointF{0, ViewportMoveDelta * (-1)});
			break;
		case Qt::Key_S:
			viewport_->moveViewInPixels(QPointF{0, ViewportMoveDelta});
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

void GameWindow::mousePressEvent(QMouseEvent *event)
{
	event->button();
	if (childAt(event->pos()) == graphicsWidget_)
		handleGameWidgetClicked(event->pos(), event->button());

	QWidget::mousePressEvent(event);
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

	//resize campPanel
	topLeft = QPoint(event->size().width() - CampPanelSize.width(),
	                 event->size().height() - CampPanelSize.height());
	campPanel_->setGeometry(QRect(topLeft, CampPanelSize));

	//set size of campEquipmentWindow
	topLeft = QPoint(0, unitsPanel_->sizeHint().height());
	widgetSize = QSize(event->size().width() / 2, event->size().height() - topLeft.y());
	campEquipmentWindow_->setGeometry(QRect(topLeft, widgetSize));
	//set size of journalWindow
	journalWindow_->setGeometry(QRect(topLeft, widgetSize));

	//set size of viewport
	viewport_->setViewSizeInPixels(QSizeF(event->size().width(), event->size().height()));

	QWidget::resizeEvent(event);
}

void GameWindow::handleGameWidgetClicked(const QPoint &pos, Qt::MouseButton button)
{
	QPointF point = viewport_->fromPixelsToMetres(pos);

	if (button == Qt::LeftButton) {
		point -= QPointF(0.1, 0.1);
		const QList<const Object *> objects = mind_->physicsEngine()->getObjectsInRect(QRectF(point, QSizeF{0.2, 0.2}));

		if (objects.isEmpty()) {
			selectObjects({});
			return;
		}

		Object *object = mind_->getObjectFromUid(objects[0]->getUid());
		selectObjects(fiterSelection({object}));
		return;
	}
	if (button == Qt::RightButton) {
		for (auto &object : selectedObjects_) {
			if (object->getType() == BS::Type::Unit) {
				Unit* unit = static_cast<Unit *>(object);
				unit->setCommand(BS::Command::Move);
				//TODO set destination with <point>
				qDebug() << "Move" << unit->getName() << "to" << point;
			}
		}
		return;
	}
}

const QList<Object *> &GameWindow::fiterSelection(const QList<Object *> &objects)
{
	//TODO
	return objects;
}

void GameWindow::selectObjects(const QList<Object *> &objects)
{
	for (auto &object : selectedObjects_)
		object->property(Properties::IsSelected) = QVariant(false);

	selectedObjects_ = objects;

	for (auto &object : selectedObjects_)
		object->property(Properties::IsSelected) = QVariant(true);
}

void GameWindow::update()
{
	campPanel_->update(mind_);
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
