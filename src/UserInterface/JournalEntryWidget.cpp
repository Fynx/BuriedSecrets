/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/JournalEntryWidget.hpp"

#include "GameObjects/JournalEntry.hpp"

const QFont JournalEntryWidget::DetailsFont{"Times", 16};
const QFont JournalEntryWidget::TitleFont{"Arial", 16, QFont::Bold};
const QMargins JournalEntryWidget::ContentMargins{0, 20, 0, 20};


JournalEntryWidget::JournalEntryWidget(JournalEntry *je)
	: entry_(je)
{
	initLayout();

	fillEntry();
}

JournalEntry *JournalEntryWidget::entry()
{
	return entry_;
}

void JournalEntryWidget::setEntry(JournalEntry* je)
{
	entry_ = je;
	fillEntry();
}

void JournalEntryWidget::initLayout()
{
	auto layout = new QVBoxLayout;
	layout->setContentsMargins(ContentMargins);
	setLayout(layout);

	title_ = new QLabel;
	title_->setFont(TitleFont);
	title_->setWordWrap(true);
	title_->setAlignment(Qt::AlignCenter);
	layout->addWidget(title_);

	text_ = new QLabel;
	text_->setFont(DetailsFont);
	text_->setWordWrap(true);
	text_->setAlignment(Qt::AlignLeft);
	layout->addWidget(text_);

	layout->addStretch();
}

void JournalEntryWidget::fillEntry()
{
	if (entry_ == nullptr) {
		title_->setText(tr("No entries yet"));
		text_->clear();
		return;
	}

	title_->setText(entry_->getTitle());
	text_->setText(entry_->getText());
}
