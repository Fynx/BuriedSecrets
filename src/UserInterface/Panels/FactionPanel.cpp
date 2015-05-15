/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Panels/FactionPanel.hpp"

#include "Mind/Mind.hpp"
#include "UserInterface/Resources.hpp"

FactionPanel::FactionPanel(const Mind *m)
	: mind_(m)
{
	setAutoFillBackground(true);

	initLayout();
}

void FactionPanel::refresh()
{
	foodAmount_->setNum(mind_->getPlayerFaction()->getFood());
}

void FactionPanel::initLayout()
{
	auto mainLayout = new QHBoxLayout;
	setLayout(mainLayout);

	QColor btnBackgroundColor(102, 102, 102);
	QPalette btnPalette(btnBackgroundColor);
	mainLayout->addLayout(createFoodLayout());

	journalBtn_ = new QPushButton;
	journalBtn_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(journalBtn_, &QPushButton::clicked, this, &FactionPanel::journalActivated);
	journalBtn_->setIcon(QIcon(Icons::Journal));
	journalBtn_->setIconSize(IconsSize);
	journalBtn_->setPalette(btnPalette);
	mainLayout->addWidget(journalBtn_);

	campBtn_ = new QPushButton;
	campBtn_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(campBtn_, &QPushButton::clicked, this, &FactionPanel::campActivated);
	campBtn_->setIcon(QIcon(Icons::Camp));
	campBtn_->setIconSize(IconsSize);
	campBtn_->setPalette(btnPalette);
	mainLayout->addWidget(campBtn_);

	exitBtn_ = new QPushButton;
	exitBtn_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(exitBtn_, &QPushButton::clicked, this, &FactionPanel::exitActivated);
	exitBtn_->setIcon(QIcon(Icons::Exit));
	exitBtn_->setIconSize(IconsSize);
	exitBtn_->setPalette(btnPalette);
	mainLayout->addWidget(exitBtn_);
}

QLayout *FactionPanel::createFoodLayout()
{
	auto foodLayout = new QHBoxLayout;

	auto foodLabel = new QLabel;
	foodLabel->setAlignment(Qt::AlignCenter);
	foodLabel->setPixmap(QPixmap(Icons::Food).scaled(IconsSize));
	foodLayout->addWidget(foodLabel);

	foodAmount_ = new QLabel;
	foodAmount_->setFont(QFont("Times", 14));
	foodAmount_->setAlignment(Qt::AlignCenter);
	foodLayout->addWidget(foodAmount_);

	return foodLayout;
}
