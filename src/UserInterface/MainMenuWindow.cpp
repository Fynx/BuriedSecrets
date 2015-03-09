/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/MainMenuWindow.hpp"

#include "General/General.hpp"

const QMargins MainMenuWindow::ContentsMargins{300, 32, 300, 32};
const int MainMenuWindow::Spacing{20};

MainMenuWindow::MainMenuWindow(const UserInterface *userInterface, QWidget *parent)
	: QWidget(parent),
	  userInterface_(userInterface)
{
	setContentsMargins(ContentsMargins);

	initButtons();
	initLayout();
}

void MainMenuWindow::adjustButtonsVisibility()
{
	continueBtn_->setVisible(userInterface_->gameInProgress());
// 	saveGameBtn_->setVisible(userInterface_->gameInProgress());
}

void MainMenuWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_Escape:
			if (userInterface_->gameInProgress())
				emit continueActivated();
			break;
		case Qt::Key_Q:
			emit quitActivated();
			break;
		default:
			QWidget::keyPressEvent(event);
	}
}

void MainMenuWindow::initButtons()
{
	QFont buttonFont("Times", 24);
	QSizePolicy btnSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	continueBtn_ = new QPushButton(tr("Continue"));
	continueBtn_->setFont(buttonFont);
	continueBtn_->setSizePolicy(btnSizePolicy);
	connect(continueBtn_, &QPushButton::clicked, this, &MainMenuWindow::continueActivated);

	newGameBtn_ = new QPushButton(tr("New game"));
	newGameBtn_->setFont(buttonFont);
	newGameBtn_->setSizePolicy(btnSizePolicy);
	connect(newGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::newGameActivated);
/*
	loadGameBtn_ = new QPushButton(tr("Load game"));
	loadGameBtn_->setFont(buttonFont);
	loadGameBtn_->setSizePolicy(btnSizePolicy);
	connect(loadGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::loadGameActivated);

	saveGameBtn_ = new QPushButton(tr("Save game"));
	saveGameBtn_->setFont(buttonFont);
	saveGameBtn_->setSizePolicy(btnSizePolicy);
	connect(saveGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::saveGameActivated);

	instructionsBtn_ = new QPushButton(tr("Instructions"));
	instructionsBtn_->setFont(buttonFont);
	instructionsBtn_->setSizePolicy(btnSizePolicy);
	connect(instructionsBtn_, &QPushButton::clicked, this, &MainMenuWindow::instructionsActivated);*/

	quitGameBtn_ = new QPushButton(tr("Quit"));
	quitGameBtn_->setFont(buttonFont);
	quitGameBtn_->setSizePolicy(btnSizePolicy);
	connect(quitGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::quitActivated);

	adjustButtonsVisibility();
}

void MainMenuWindow::initLayout()
{
	auto mainLayout = new QVBoxLayout;
	mainLayout->setSpacing(Spacing);
	this->setLayout(mainLayout);

	auto title = new QLabel(tr("Buried Secrets"));
	title->setFont(QFont("Times", 36));
	title->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(title, 3);

	mainLayout->addWidget(continueBtn_, 1);
	mainLayout->addWidget(newGameBtn_, 1);
// 	mainLayout->addWidget(loadGameBtn_,1);
// 	mainLayout->addWidget(saveGameBtn_, 1);
// 	mainLayout->addWidget(instructionsBtn_, 1);
	mainLayout->addWidget(quitGameBtn_, 1);
	mainLayout->addStretch(3);
}
