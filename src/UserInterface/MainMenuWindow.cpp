/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/MainMenuWindow.hpp"

#include "General/General.hpp"

MainMenuWindow::MainMenuWindow(const UserInterface *userInterface, QWidget *parent)
	: QWidget(parent),
	  userInterface_(userInterface)
{
	initButtons();
	initLayout();
}

void MainMenuWindow::adjustButtonsVisibility()
{
	continueBtn_->setVisible(userInterface_->gameInProgress());
	saveGameBtn_->setVisible(userInterface_->gameInProgress());
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
	continueBtn_ = new QPushButton("Continue");
	connect(continueBtn_, &QPushButton::clicked, this, &MainMenuWindow::continueActivated);

	newGameBtn_ = new QPushButton("New game");
	connect(newGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::newGameActivated);

	loadGameBtn_ = new QPushButton("Load game");
	connect(loadGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::loadGameActivated);

	saveGameBtn_ = new QPushButton("Save game");
	connect(saveGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::saveGameActivated);

	instructionsBtn_ = new QPushButton("Instructions");
	connect(instructionsBtn_, &QPushButton::clicked, this, &MainMenuWindow::instructionsActivated);

	quitGameBtn_ = new QPushButton("Quit");
	connect(quitGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::quitActivated);

	adjustButtonsVisibility();
}

void MainMenuWindow::initLayout()
{
	QVBoxLayout *mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	mainLayout->addWidget(new QLabel("Buried Secrets"));
	mainLayout->addWidget(continueBtn_);
	mainLayout->addWidget(newGameBtn_);
	mainLayout->addWidget(loadGameBtn_);
	mainLayout->addWidget(saveGameBtn_);
	mainLayout->addWidget(instructionsBtn_);
	mainLayout->addWidget(quitGameBtn_);
	mainLayout->addStretch();
}
