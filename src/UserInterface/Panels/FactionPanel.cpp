/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Panels/FactionPanel.hpp"

#include "Mind/Mind.hpp"
#include "UserInterface/Resources.hpp"

FactionPanel::FactionPanel()
{
	setAutoFillBackground(true);

	initLayout();
}

void FactionPanel::refresh(const Mind *mind)
{
	foodAmount_->setNum(mind->getPlayerFaction()->getFood());

	if (campIconFlash_)
		campBtn_->setIcon(QIcon(Icons::CampSelected));
	else
		campBtn_->setIcon(QIcon(Icons::Camp));
}

void FactionPanel::setCampIconFlash(bool flash)
{
	campIconFlash_ = flash;
}

void FactionPanel::initLayout()
{
	auto mainLayout = new QHBoxLayout;
	setLayout(mainLayout);

	journalBtn_ = new QPushButton;
	journalBtn_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(journalBtn_, &QPushButton::clicked, this, &FactionPanel::journalActivated);
	journalBtn_->setIcon(QIcon(Icons::Journal));
	journalBtn_->setIconSize(IconsSize);
	mainLayout->addWidget(journalBtn_);

	campBtn_ = new QPushButton;
	campBtn_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(campBtn_, &QPushButton::clicked, this, &FactionPanel::campActivated);
	campBtn_->setIcon(QIcon(Icons::Camp));
	campBtn_->setIconSize(IconsSize);
	mainLayout->addWidget(campBtn_);

	mainLayout->addLayout(createFoodLayout());
}

QLayout* FactionPanel::createFoodLayout()
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
