/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "SlotWidget.hpp"

#include "UserInterface/Resources.hpp"
#include "GameObjects/Object.hpp"

const QSize SlotWidget::MiniatureSize {32, 32};

SlotWidget::SlotWidget(BS::Slot slot)
	: SlotWidget(slot, QPixmap(Icons::Empty), {tr("empty")}, Object::InvalidUid)
{}

SlotWidget::SlotWidget(BS::Slot slot, QPixmap pixmap, const QString &text, int itemUid)
	: slot_(slot)
{
	initLayout();

	setItem(pixmap, text, itemUid);
	setFrameShape(QFrame::Panel);
	setFrameShadow(QFrame::Plain);
	setLineWidth(1);
}

void SlotWidget::setItem(const QPixmap &pixmap, const QString &text, int itemUid)
{
	miniature_->setPixmap(pixmap. scaled(MiniatureSize));
	text_->setText(text);
	itemUid_ = itemUid;
}

BS::Slot SlotWidget::slot() const
{
	return slot_;
}

int SlotWidget::itemUid() const
{
	return itemUid_;
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
