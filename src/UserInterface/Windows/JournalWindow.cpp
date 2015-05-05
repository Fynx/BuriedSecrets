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

const QFont JournalWindow::LabelsFont{"Times", 14};
const QString JournalWindow::FilterAll(tr("All"));
//NOTE strings in Filters must be unique.
const QMap<QString, QSet<BS::EntryType>> JournalWindow::Filters{
	{FilterAll,    {BS::EntryType::Death, BS::EntryType::Help, BS::EntryType::Quest, BS::EntryType::Psycho}},
	{tr("Units"),  {BS::EntryType::Death, BS::EntryType::Psycho}},
	{tr("Help"),   {BS::EntryType::Help}},
	{tr("Quest"),  {BS::EntryType::Quest}},
};

JournalWindow::JournalWindow(Mind *m, DataManager *dm)
	: mind_(m),
	  dataManager_(dm)
{
	closeBtn_ = new QPushButton(tr("Close"));
	connect(closeBtn_, &QPushButton::clicked, this, &JournalWindow::exit);

	setAutoFillBackground(true);

	initLayout();
	connect(&filtersMapper_, static_cast<void (QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped),
			this, &JournalWindow::onFilterClicked);
	connect(entriesList_, &QListWidget::currentItemChanged,
	        this, &JournalWindow::onCurrentEntryChanged);
}

void JournalWindow::refresh()
{
	entriesList_->clear();

	auto entries = mind_->getPlayerFaction()->getJournal()->getEntries();

	auto filteredTypes = Filters[currentFilter_];
	for (auto entry : entries) {
		if (! JournalEntry::hasLongForm(entry->getEntryType()))
			continue;

		if (! filteredTypes.contains(entry->getEntryType()))
			continue;

		auto lwi = new QListWidgetItem(entry->getTitle(), entriesList_);
		lwi->setFlags(Qt::ItemFlag::ItemIsSelectable | Qt::ItemIsEnabled);
		lwi->setData(Qt::UserRole, entry->getUid());
		lwi->setFont(QFont("Times", 16));
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

	if (! Filters[currentFilter_].contains(entry->getEntryType()))
		onFilterClicked(FilterAll);

	journalEntryWidget_->setEntry(entry);
}

void JournalWindow::initLayout()
{
	auto layout  = new QVBoxLayout;
	setLayout(layout);

	auto title = new QLabel(tr("Journal"));
	title->setFont(QFont("Times", 18));
	layout->addWidget(title);

	auto hLayout = new QHBoxLayout;
	layout->addLayout(hLayout, 1);

	auto vLayout = new QVBoxLayout;
	vLayout->addLayout(createFiltersButtons());
	entriesList_ = new QListWidget;
	vLayout->addWidget(entriesList_, 1);
	hLayout->addLayout(vLayout, 1);

	journalEntryWidget_ = new JournalEntryWidget;
	hLayout->addWidget(journalEntryWidget_, 2);

	layout->addWidget(closeBtn_);
}

QLayout *JournalWindow::createFiltersButtons()
{
	auto layout = new QHBoxLayout;
/*
	auto label = new QLabel(tr("Filters"));
	label->setFont(LabelsFont);
	layout->addWidget(label);*/

	for (auto filter : Filters.keys()) {
		auto btn = new QPushButton(filter);
		btn->setFont(LabelsFont);
		connect(btn, &QPushButton::clicked,
		        &filtersMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
		filtersMapper_.setMapping(btn, filter);
		filters_[filter] = btn;
		layout->addWidget(btn);
	}

	currentFilter_ = FilterAll;
	filters_[FilterAll]->setFlat(true);

	return layout;
}

void JournalWindow::onFilterClicked(const QString &filterName)
{
	filters_[currentFilter_]->setFlat(false);
	filters_[filterName]->setFlat(true);
	currentFilter_ = filterName;

	refresh();
}

void JournalWindow::onCurrentEntryChanged(QListWidgetItem *item)
{
	if (item)
		setCurrentEntry(item->data(Qt::UserRole).toInt());
}
