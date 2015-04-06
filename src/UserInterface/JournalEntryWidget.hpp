/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class JournalEntry;

class JournalEntryWidget : public QWidget {

public:
	static const QFont TitleFont;
	static const QFont DetailsFont;
	static const QMargins ContentMargins;

	JournalEntryWidget(JournalEntry *je = nullptr);

	JournalEntry *entry();
	void setEntry(JournalEntry *je);

private:
	void initLayout();
	void fillEntry();

	JournalEntry *entry_;
	QLabel *title_;
	QLabel *text_;
};
