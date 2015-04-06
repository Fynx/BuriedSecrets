/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Panels/NotificationWidget.hpp"

#include "GameObjects/JournalEntry.hpp"

NotificationWidget::NotificationWidget(JournalEntry *entry)
	: entry_(entry)
{
	setAutoFillBackground(true);
	setFrameStyle(QFrame::Box | QFrame::Plain);
	setLineWidth(1);
	setLayout(new QVBoxLayout);

	layout()->addWidget(new QLabel(entry->getTitle()));
}

void NotificationWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
		emit notificationClicked(entry_->getUid());

    QWidget::mousePressEvent(event);
}
