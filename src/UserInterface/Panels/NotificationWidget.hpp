/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class JournalEntry;

class NotificationWidget : public QFrame {
	Q_OBJECT
public:
	NotificationWidget(JournalEntry *entry);

protected:
	void mousePressEvent(QMouseEvent *event);

private:
	JournalEntry *entry_;

signals:
	void notificationClicked(int uid);
};
