/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/Tabs/Item/ItemsListWidget.hpp"

#include "UserInterface/Windows/Tabs/Item/SlotWidget.hpp"

ItemsListWidget::ItemsListWidget(QWidget *parent)
	: QListWidget(parent),
	  dragAndDropEnabled_(true)
{
	setAcceptDrops(true);
}

void ItemsListWidget::disableDragAndDrop()
{
	dragAndDropEnabled_ = false;
}

void ItemsListWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		dragStartPos_ = event->pos();
	QListWidget::mousePressEvent(event);
}

void ItemsListWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - dragStartPos_).manhattanLength();
		if (distance >= QApplication::startDragDistance())
			performDrag();
	}
	QListWidget::mouseMoveEvent(event);
}

void ItemsListWidget::dragEnterEvent(QDragEnterEvent *event)
{
	dragMoveEvent(event);
}

void ItemsListWidget::dragMoveEvent(QDragMoveEvent *event)
{
	if (!dragAndDropEnabled_ || event->source() == this) {
		event->ignore();
		return;
	}

	ItemsListWidget *ilw = qobject_cast<ItemsListWidget *>(event->source());
	if (ilw && event->possibleActions() & Qt::MoveAction) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
		return;
	}

	else
		event->ignore();
}

void ItemsListWidget::dropEvent(QDropEvent *event)
{
	if (event->possibleActions() & Qt::MoveAction) {
		event->setDropAction(Qt::MoveAction);
		emit itemMovedIn(QVariant(event->mimeData()->data("uid")).toInt());
		event->accept();
		return;
	}

	event->ignore();
}

void ItemsListWidget::performDrag()
{
	if (!dragAndDropEnabled_)
		return;

	QListWidgetItem *item = currentItem();
	if (item == nullptr)
		return;

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("uid", item->data(Qt::UserRole).toByteArray());

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setPixmap(QPixmap(item->icon().pixmap(32, 32)));

	auto result = drag->exec(Qt::MoveAction);
	if (result == Qt::MoveAction) {
		emit itemMovedOut(item->data(Qt::UserRole).toInt());
	}
}
