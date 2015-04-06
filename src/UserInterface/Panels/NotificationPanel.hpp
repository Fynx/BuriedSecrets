/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class JournalEntry;
class Mind;
class NotificationWidget;

class NotificationPanel : public QObject {
	Q_OBJECT
public:
	NotificationPanel(Mind *m, DataManager *dm, QWidget *mainWidget);

	void adjustPanelGeometry(const QRect &mainWindowGeometry, const QSize &unitsPanelSize);
	void refresh();

private:
	static const int PanelWidth;
	static const int PanelHeight;
	static const int DisplayLimit;
	static const int DisplayTime;
	static const int TimerInterval;
	static const QSize NotificationSize;

	NotificationWidget *createNotification(JournalEntry *entry);
    void updatePositions();

	Mind *const mind_;
	DataManager *const dataManager_;
	QWidget *const mainWidget_;

	int knownJournalEntries_;
	QRect availableSize_;
	QVector<QPair<NotificationWidget*, int>> displayedNotifications_;
	QQueue<JournalEntry *> entriesToShow_;
	QTimer *notificationTimer_;

private slots:
	void updateNotifications();

signals:
	void notificationClicked(int uid);
};
