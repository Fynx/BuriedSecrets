/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/MainMenuWindow.hpp"
#include "General/General.hpp"

MainMenuWindow::MainMenuWindow(General *general, QWidget *parent) : QWidget(parent), gameInProgress(false), general(general)
{
	initButtons();
	initLayout();
}

void MainMenuWindow::initButtons()
{
	continueBtn = new QPushButton("Continue");
	connect(continueBtn, &QPushButton::clicked, this, &MainMenuWindow::onContinueActivated);

	newGameBtn = new QPushButton("New game");
	connect(newGameBtn, &QPushButton::clicked, this, &MainMenuWindow::onNewGameActivated);

	loadGameBtn = new QPushButton("Load game");
	connect(loadGameBtn, &QPushButton::clicked, this, &MainMenuWindow::onLoadGameActivated);

	saveGameBtn = new QPushButton("Save game");
	connect(saveGameBtn, &QPushButton::clicked, this, &MainMenuWindow::onSaveGameActivated);

	instructionsBtn = new QPushButton("Instructions");
	connect(instructionsBtn, &QPushButton::clicked, this, &MainMenuWindow::onInstructionsActivated);

	quitGameBtn = new QPushButton("Quit");
	connect(quitGameBtn, &QPushButton::clicked, this, &MainMenuWindow::onQuitActivated);

	adjustButtonsVisibility();
}

void MainMenuWindow::initLayout()
{
	QVBoxLayout *mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	mainLayout->addWidget(new QLabel("Buried Secrets"));
	mainLayout->addWidget(continueBtn);
	mainLayout->addWidget(newGameBtn);
	mainLayout->addWidget(loadGameBtn);
	mainLayout->addWidget(saveGameBtn);
	mainLayout->addWidget(instructionsBtn);
	mainLayout->addWidget(quitGameBtn);
	mainLayout->addStretch();
}

void MainMenuWindow::adjustButtonsVisibility()
{
	continueBtn->setVisible(gameInProgress);
	saveGameBtn->setVisible(gameInProgress);
}

void MainMenuWindow::onContinueActivated()
{
	emit switchToGame();
}

void MainMenuWindow::onNewGameActivated()
{
	gameInProgress = true;
	//WARNING with next two lines in different order
	//        general starts game with game window widgets not yet initialized
	emit switchToGame();
	general->newGameStarted();
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
