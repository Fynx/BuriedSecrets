/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/Tabs/BriefingTab.hpp"

#include "GameObjects/JournalEntry.hpp"

const QFont BriefingTab::DetailsFont{"Times", 16};
const QFont BriefingTab::TitleFont{"Arial", 16, QFont::Bold};
const QMargins BriefingTab::ContentMargins{30, 20, 30, 20};


BriefingTab::BriefingTab(const QString &title, const QString &text)
	: QWidget(),
	  title_(title),
	  text_(text)
{
	initLayout();
}

void BriefingTab::initLayout()
{
	auto layout = new QVBoxLayout;
	layout->setContentsMargins(ContentMargins);
	setLayout(layout);

	auto titleLabel = new QLabel(title_);
	titleLabel->setFont(TitleFont);
	titleLabel->setWordWrap(true);
	titleLabel->setAlignment(Qt::AlignCenter);
	layout->addWidget(titleLabel);

	auto textLabel = new QLabel(text_);
	textLabel->setFont(DetailsFont);
	textLabel->setWordWrap(true);
	textLabel->setAlignment(Qt::AlignLeft);
	layout->addWidget(textLabel);

	layout->addStretch();
}
