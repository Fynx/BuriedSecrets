/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "JournalWindow.hpp"

JournalWindow::JournalWindow()
{
	closeBtn_ = new QPushButton("Close");
	connect(closeBtn_, &QPushButton::clicked, this, &JournalWindow::exit);

	setAutoFillBackground(true);

	initLayout();
}

void JournalWindow::initLayout()
{
	QVBoxLayout *layout  = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(new QLabel("Journal"));
	layout->addStretch();
	layout->addWidget(closeBtn_);
}
