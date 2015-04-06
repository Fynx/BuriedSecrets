/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/JournalWindow.hpp"
#include "UserInterface/JournalEntryWidget.hpp"

#include "Mind/Mind.hpp"
#include "DataManager/DataManager.hpp"

JournalWindow::JournalWindow(Mind *m, DataManager *dm)
	: mind_(m),
	  dataManager_(dm),
	  journal_(m->getPlayerFaction()->getJournal())
{
	closeBtn_ = new QPushButton(tr("Close"));
	connect(closeBtn_, &QPushButton::clicked, this, &JournalWindow::exit);

	setAutoFillBackground(true);

	initLayout();
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
	hLayout->addWidget(journalEntryWidget_, 1);

	layout->addWidget(closeBtn_);
}
