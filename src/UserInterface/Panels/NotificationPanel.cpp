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
const QSize NotificationPanel::NotificationSize{250, 50};

NotificationPanel::NotificationPanel(Mind *m, DataManager *dm, QWidget *mainWidget)
	: mind_(m),
	  dataManager_(dm),
	  mainWidget_(mainWidget),
	  knownJournalEntries_(0)
{
	connect(&notificationTimer_, &QTimer::timeout, this, &NotificationPanel::updateNotifications);
	notificationTimer_.start(TimerInterval);
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
		while (knownJournalEntries_ < journal->getEntries().size()) {
			auto entry = journal->getEntry(knownJournalEntries_++);
			if (JournalEntry::hasNotification(entry->getEntryType()))
				entriesToShow_.push_back(entry);
		}
	}
}

void NotificationPanel::updateNotifications()
{
	int inQueueBefore = entriesToShow_.size();
	QList<int> toRemove;
	for (int i = 0; i < displayedNotifications_.count(); ++i) {
		displayedNotifications_[i].second -= TimerInterval;
		if (displayedNotifications_[i].second <= 0)
			toRemove.push_back(i);
	}
	//WARNING since we remove by indexes it is important to remove higher first
	while (! toRemove.isEmpty()) {
		auto idx = toRemove.takeLast();
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
	if (JournalEntry::hasLongForm(entry->getEntryType()))
		connect(notif, &NotificationWidget::notificationClicked,
		        this, &NotificationPanel::notificationClicked);
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
