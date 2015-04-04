/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/Tabs/Item/SlotWidget.hpp"

#include "UserInterface/Resources.hpp"
#include "GameObjects/Object.hpp"
#include "UserInterface/Windows/Tabs/Item/ItemsListWidget.hpp"

const QSize SlotWidget::MiniatureSize {48, 48};

SlotWidget::SlotWidget(BS::Slot slot)
	: SlotWidget(slot, QPixmap(Icons::Empty), {}, Object::InvalidUid)
{}

SlotWidget::SlotWidget(BS::Slot slot, QPixmap pixmap, const QString &text, int itemUid)
	: slot_(slot)
{
	initLayout();

	setAcceptDrops(true);

	setItem(pixmap, text, itemUid);
	setFrameShape(QFrame::Panel);
	setFrameShadow(QFrame::Plain);
	setLineWidth(1);
}

void SlotWidget::setItem(const QPixmap &pixmap, const QString &text, int itemUid)
{
	miniature_->setPixmap(pixmap.scaled(MiniatureSize));
	text_->setText(text);
	itemUid_ = itemUid;
}

void SlotWidget::clearItem()
{
	miniature_->setPixmap(QPixmap(Icons::Empty).scaled(MiniatureSize));
	text_->setText({});
	itemUid_ = Object::InvalidUid;
}

void SlotWidget::markEnabled(bool enabled)
{
	if (enabled)
		setLineWidth(3);
	else
		setLineWidth(1);
}

void SlotWidget::markLinked(bool linked)
{
	if (linked)
		setFrameShadow(QFrame::Raised);
	else
		setFrameShadow(QFrame::Plain);
}

BS::Slot SlotWidget::slot() const
{
	return slot_;
}

int SlotWidget::itemUid() const
{
	return itemUid_;
}

void SlotWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		dragStartPos_ = event->pos();

    QWidget::mousePressEvent(event);
}

void SlotWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - dragStartPos_).manhattanLength();
		if (distance >= QApplication::startDragDistance())
			performDrag();
	}
    QWidget::mouseMoveEvent(event);
}

void SlotWidget::dragEnterEvent(QDragEnterEvent *event)
{
	dragMoveEvent(event);
}

void SlotWidget::dragMoveEvent(QDragMoveEvent* event)
{
	if (event->source() == this) {
		event->ignore();
		return;
	}
	ItemsListWidget *ilw = qobject_cast<ItemsListWidget *>(event->source());
	if (ilw && event->possibleActions() & Qt::LinkAction) {
		event->setDropAction(Qt::LinkAction);
		event->accept();
		return;
	}
		event->ignore();
}

void SlotWidget::dropEvent(QDropEvent *event)
{
	if (event->possibleActions() & Qt::LinkAction) {
		event->setDropAction(Qt::LinkAction);
		emit itemLinkedIn(slot_, QVariant(event->mimeData()->data("uid")).toInt());
		event->accept();
		return;
	}

	event->ignore();
}

void SlotWidget::performDrag()
{
	if (itemUid_ == Object::InvalidUid)
		return;

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("uid", QVariant(itemUid_).toByteArray());

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setPixmap(*miniature_->pixmap());

	if (drag->exec(Qt::LinkAction) == Qt::LinkAction)
		emit itemLinkedOut(slot_, itemUid_);
}

void SlotWidget::initLayout()
{
	auto layout = new QHBoxLayout;
	setLayout(layout);

	miniature_ = new QLabel;
	layout->addWidget(miniature_);

	text_ = new QLabel;
	text_->setFont(QFont("Times", 16));
	layout->addWidget(text_);

	layout->addStretch();
}
