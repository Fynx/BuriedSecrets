/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "PostGameWindow.hpp"

PostGameWindow::PostGameWindow(): QWidget()
{
	initLayout();

	connect(mainMenuBtn_, &QPushButton::clicked, this, &PostGameWindow::goToMainMenu);
}

void PostGameWindow::setEnding(BS::GameState gs)
{
	switch(gs) {
		case BS::GameState::Lost:
			textLabel_->setText(tr("All your units are dead.\nGAME OVER"));
			break;
		case BS::GameState::Won:
			textLabel_->setText(tr("You have won, congratulations.\nYOU ARE AWESOME!"));
			break;
		default:
			textLabel_->setText(tr("Sth went wrong, we are sorry."));
			break;
	}
}

void PostGameWindow::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	textLabel_ = new QLabel;
	textLabel_->setFont(QFont("Times", 36));
	textLabel_->setAlignment(Qt::AlignCenter);
	layout->addWidget(textLabel_, 1);

	mainMenuBtn_ = new QPushButton(tr("Go to MainMenu"));
	mainMenuBtn_->setFont(QFont("Times", 24));
	layout->addWidget(mainMenuBtn_, 1);

	layout->addStretch(1);
}
