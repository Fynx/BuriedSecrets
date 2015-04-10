/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/JournalWindow.hpp"

#include "DataManager/DataManager.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Journal.hpp"
#include "GameObjects/JournalEntry.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/JournalEntryWidget.hpp"

JournalWindow::JournalWindow(Mind *m, DataManager *dm)
	: mind_(m),
	  dataManager_(dm)
{
	closeBtn_ = new QPushButton(tr("Close"));
	connect(closeBtn_, &QPushButton::clicked, this, &JournalWindow::exit);

	setAutoFillBackground(true);

	initLayout();
	connect(entriesList_, &QListWidget::currentItemChanged, this, &JournalWindow::onCurrentEntryChanged);
}

void JournalWindow::refresh()
{
	auto entries = mind_->getPlayerFaction()->getJournal()->getEntries();

	for (auto entry : entries) {
		if (! JournalEntry::hasLongForm(entry->getEntryType()))
			continue;

		auto lwi = new QListWidgetItem(entry->getTitle(), entriesList_);
		lwi->setFlags(Qt::ItemFlag::ItemIsSelectable | Qt::ItemIsEnabled);
		lwi->setData(Qt::UserRole, entry->getUid());
		lwi->setFont(QFont("Times", 18));
	}

	if (entriesList_->count() > 0)
		entriesList_->setCurrentRow(0);
}

void JournalWindow::setCurrentEntry(int uid)
{
	auto entry = dynamic_cast<JournalEntry *>(mind_->getObjectFromUid(uid));
	if (!entry) {
		warn(QString::number(uid) + QString(" is not valid journal entry."));
		return;
	}
	journalEntryWidget_->setEntry(entry);
}

void JournalWindow::initLayout()
{
	auto layout  = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(new QLabel(tr("Journal")));

	auto hLayout = new QHBoxLayout;
	layout->addLayout(hLayout, 1);

	entriesList_ = new QListWidget;
	hLayout->addWidget(entriesList_, 1);
	journalEntryWidget_ = new JournalEntryWidget;
	hLayout->addWidget(journalEntryWidget_, 2);

	layout->addWidget(closeBtn_);
}

void JournalWindow::onCurrentEntryChanged(QListWidgetItem *item)
{
	setCurrentEntry(item->data(Qt::UserRole).toInt());
}
