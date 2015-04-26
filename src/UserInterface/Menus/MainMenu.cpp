/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/Menus/MainMenu.hpp"

#include "General/General.hpp"

const QMargins MainMenu::ContentsMargins{300, 32, 300, 32};
const int MainMenu::Spacing{20};

MainMenu::MainMenu(const UserInterface *userInterface, QWidget *parent)
	: QWidget(parent),
	  userInterface_(userInterface)
{
	setContentsMargins(ContentsMargins);

	initButtons();
	initLayout();
}

void MainMenu::adjustButtonsVisibility()
{
	continueBtn_->setVisible(userInterface_->gameInProgress());
	saveGameBtn_->setVisible(userInterface_->gameInProgress());
	//TMP due to WTF
	loadGameBtn_->setVisible(userInterface_->gameInProgress());
}

void MainMenu::keyPressEvent(QKeyEvent *event)
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

void MainMenu::initButtons()
{
	QFont buttonFont("Times", 24);
	QSizePolicy btnSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	continueBtn_ = new QPushButton(tr("Continue"));
	continueBtn_->setFont(buttonFont);
	continueBtn_->setSizePolicy(btnSizePolicy);
	connect(continueBtn_, &QPushButton::clicked, this, &MainMenu::continueActivated);

	newGameBtn_ = new QPushButton(tr("New game"));
	newGameBtn_->setFont(buttonFont);
	newGameBtn_->setSizePolicy(btnSizePolicy);
	connect(newGameBtn_, &QPushButton::clicked, this, &MainMenu::newGameActivated);

	loadGameBtn_ = new QPushButton(tr("Load game"));
	loadGameBtn_->setFont(buttonFont);
	loadGameBtn_->setSizePolicy(btnSizePolicy);
	connect(loadGameBtn_, &QPushButton::clicked, this, &MainMenu::loadGameActivated);

	saveGameBtn_ = new QPushButton(tr("Save game"));
	saveGameBtn_->setFont(buttonFont);
	saveGameBtn_->setSizePolicy(btnSizePolicy);
	connect(saveGameBtn_, &QPushButton::clicked, this, &MainMenu::saveGameActivated);

	quitGameBtn_ = new QPushButton(tr("Quit"));
	quitGameBtn_->setFont(buttonFont);
	quitGameBtn_->setSizePolicy(btnSizePolicy);
	connect(quitGameBtn_, &QPushButton::clicked, this, &MainMenu::quitActivated);

	adjustButtonsVisibility();
}

void MainMenu::initLayout()
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
	mainLayout->addWidget(loadGameBtn_,1);
	mainLayout->addWidget(saveGameBtn_, 1);
	mainLayout->addWidget(quitGameBtn_, 1);
	mainLayout->addStretch(3);
}
