/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class JournalEntry;

class NotificationWidget : public QFrame {
public:
	NotificationWidget(JournalEntry *entry);
};
