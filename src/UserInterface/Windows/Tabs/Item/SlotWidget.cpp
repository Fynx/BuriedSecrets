/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/Tabs/Item/SlotWidget.hpp"

#include "UserInterface/Windows/Tabs/UnitEquipmentTab.hpp"
#include "UserInterface/Resources.hpp"
#include "GameObjects/Object.hpp"
#include "UserInterface/Windows/Tabs/Item/ItemsListWidget.hpp"

const QSize SlotWidget::MiniatureSize {48, 48};

SlotWidget::SlotWidget(UnitEquipmentTab *uet, BS::Slot slot)
	: SlotWidget(uet, slot, QPixmap(Icons::Empty), {}, Object::InvalidUid)
{}

SlotWidget::SlotWidget(UnitEquipmentTab *uet, BS::Slot slot,
                       QPixmap pixmap, const QString &text, int itemUid)
	: unitEquipmentTab_(uet), slot_(slot)
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

void SlotWidget::setMarked(bool isMarked)
{
	if (isMarked)
		setFrameShadow(QFrame::Raised);
// 		setLineWidth(3);
	else
		setFrameShadow(QFrame::Plain);
// 		setLineWidth(1);
}

bool SlotWidget::isEmpty() const
{
	return itemUid_ == Object::InvalidUid;
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
	if (!isEmpty())
		emit slotActivated(itemUid_);

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
	if (event->isAccepted())
		setMarked(true);
}

void SlotWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
	setMarked(false);
}

void SlotWidget::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->source() == this) {
		event->ignore();
		return;
	}

	int uid = QVariant(event->mimeData()->data("uid")).toInt();

	if (unitEquipmentTab_->isAcceptableItem(uid, slot_)) {
		event->accept();
		return;
	}

	event->ignore();
}

void SlotWidget::dropEvent(QDropEvent *event)
{
	if (event->possibleActions() & Qt::MoveAction) {
		event->setDropAction(Qt::MoveAction);
		event->accept();

		emit itemMovedIn(slot_, QVariant(event->mimeData()->data("uid")).toInt());

		setMarked(false);
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

	if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
		emit itemMovedOut(slot_, itemUid_);
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
