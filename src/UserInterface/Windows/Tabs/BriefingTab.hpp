/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class BriefingTab : public QWidget {

public:
	static const QFont TitleFont;
	static const QFont DetailsFont;
	static const QMargins ContentMargins;

	BriefingTab(const QString &title, const QString &text);

private:
	void initLayout();

	QString title_;
	QString text_;
};
