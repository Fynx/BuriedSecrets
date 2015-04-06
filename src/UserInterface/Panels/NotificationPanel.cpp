/* YoLoDevelopment, 2015
 * All rights reserved.
 */

#include "UserInterface/Panels/NotificationPanel.hpp"

#include "Mind/Mind.hpp"
#include "GameObjects/Journal.hpp"
#include "UserInterface/Panels/NotificationWidget.hpp"

const int NotificationPanel::PanelWidth = 200;
const int NotificationPanel::PanelHeight = 500;
const int NotificationPanel::DisplayLimit = 8;
const int NotificationPanel::DisplayTime = 3000;
const int NotificationPanel::TimerInterval = 100;
const QSize NotificationPanel::NotificationSize{200, 50};

NotificationPanel::NotificationPanel(Mind *m, DataManager *dm, QWidget *mainWidget)
	: mind_(m),
	  dataManager_(dm),
	  mainWidget_(mainWidget),
	  knownJournalEntries_(0),
	  notificationTimer_(new QTimer)
{
	connect(notificationTimer_, &QTimer::timeout, this, &NotificationPanel::updateNotifications);
	notificationTimer_->start(TimerInterval);
}

void NotificationPanel::adjustPanelGeometry(const QRect &mainWindowGeometry, const QSize &unitsPanelSize)
{
	availableSize_ = mainWindowGeometry;
	availableSize_.setTop(unitsPanelSize.height());
	availableSize_.setWidth(PanelWidth);
	availableSize_.setHeight(PanelHeight);
}

void NotificationPanel::refresh()
{
	auto journal = mind_->getPlayerFaction()->getJournal();

	if (journal->getEntries().size() > knownJournalEntries_){
		while (knownJournalEntries_ < journal->getEntries().size())
			entriesToShow_.push_back(journal->getEntry(knownJournalEntries_++));
	}
}

void NotificationPanel::updateNotifications()
{
	int inQueueBefore = entriesToShow_.size();
	QSet<int> toRemove;
	for (int i = 0; i < displayedNotifications_.count(); ++i) {
		displayedNotifications_[i].second -= TimerInterval;
		if (displayedNotifications_[i].second <= 0)
			toRemove.insert(i);
	}
	for (auto idx : toRemove){
		delete displayedNotifications_[idx].first;
		displayedNotifications_.remove(idx);
	}

	while (displayedNotifications_.count() < DisplayLimit && ! entriesToShow_.isEmpty())
		displayedNotifications_.append({createNotification(entriesToShow_.takeFirst()), DisplayTime});

	if (entriesToShow_.size() != inQueueBefore || !toRemove.isEmpty())
		updatePositions();
}

NotificationWidget *NotificationPanel::createNotification(JournalEntry *entry)
{
	auto notif = new NotificationWidget(entry);
	connect(notif, &NotificationWidget::notificationClicked, this, &NotificationPanel::notificationClicked);
	notif->setParent(mainWidget_);
	notif->resize(NotificationSize);
	notif->show();
	return notif;
}

void NotificationPanel::updatePositions()
{
	for (int i = 0; i < displayedNotifications_.count(); ++i) {
		QPoint point = availableSize_.topLeft();
		point += QPoint{0, NotificationSize.height() * (i + 1)};
		displayedNotifications_[i].first->move(point);
	}
}
