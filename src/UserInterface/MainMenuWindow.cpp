/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/MainMenuWindow.hpp"
#include "General/General.hpp"

MainMenuWindow::MainMenuWindow(DataManager *dataManager, General *general, QWidget *parent)
	: QWidget(parent),
	  gameInProgress_(false),
	  dataManager_(dataManager),
	  general_(general)
{
	initButtons();
	initLayout();
}

void MainMenuWindow::initButtons()
{
	continueBtn_ = new QPushButton("Continue");
	connect(continueBtn_, &QPushButton::clicked, this, &MainMenuWindow::onContinueActivated);

	newGameBtn_ = new QPushButton("New game");
	connect(newGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::onNewGameActivated);

	loadGameBtn_ = new QPushButton("Load game");
	connect(loadGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::onLoadGameActivated);

	saveGameBtn_ = new QPushButton("Save game");
	connect(saveGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::onSaveGameActivated);

	instructionsBtn_ = new QPushButton("Instructions");
	connect(instructionsBtn_, &QPushButton::clicked, this, &MainMenuWindow::onInstructionsActivated);

	quitGameBtn_ = new QPushButton("Quit");
	connect(quitGameBtn_, &QPushButton::clicked, this, &MainMenuWindow::onQuitActivated);

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

void MainMenuWindow::adjustButtonsVisibility()
{
	continueBtn_->setVisible(gameInProgress_);
	saveGameBtn_->setVisible(gameInProgress_);
}

void MainMenuWindow::onContinueActivated()
{
	emit switchToGame();
}

void MainMenuWindow::onNewGameActivated()
{
	gameInProgress_ = true;
	//WARNING with next two lines in different order
	//        general starts game with game window widgets not yet initialized
	emit switchToGame();
	general_->newGameStarted();
	adjustButtonsVisibility();
}

void MainMenuWindow::onLoadGameActivated()
{

}

void MainMenuWindow::onSaveGameActivated()
{

}

void MainMenuWindow::onInstructionsActivated()
{

}

void MainMenuWindow::onQuitActivated()
{
	emit quit();
}
