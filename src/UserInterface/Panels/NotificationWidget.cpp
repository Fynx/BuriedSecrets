/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Panels/NotificationWidget.hpp"

#include "GameObjects/JournalEntry.hpp"

NotificationWidget::NotificationWidget(JournalEntry *entry)
{
	setAutoFillBackground(true);
	setLayout(new QVBoxLayout);

	layout()->addWidget(new QLabel(entry->getTitle()));
}
