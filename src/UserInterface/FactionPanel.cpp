/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "FactionPanel.hpp"

#include "Mind/Mind.hpp"

FactionPanel::FactionPanel()
{
	setAutoFillBackground(true);

	initLayout();
}

void FactionPanel::refresh(const Mind *mind)
{
	foodAmount_->setNum(mind->getPlayerFaction()->getFood());
}

void FactionPanel::initLayout()
{
	auto mainLayout = new QHBoxLayout;
	setLayout(mainLayout);

	journalBtn_ = new QPushButton("Journal");
	journalBtn_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(journalBtn_, &QPushButton::clicked, this, &FactionPanel::journalActivated);
	mainLayout->addWidget(journalBtn_);

	campBtn_ = new QPushButton("Camp EQ");
	campBtn_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(campBtn_, &QPushButton::clicked, this, &FactionPanel::campActivated);
	mainLayout->addWidget(campBtn_);

	mainLayout->addLayout(createFoodLayout());
}

QLayout* FactionPanel::createFoodLayout()
{
	auto foodLayout = new QVBoxLayout;

	QFont font("Times", 14);

	auto foodLabel = new QLabel;
	foodLabel->setFont(font);
	foodLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	foodLabel->setText(tr("Food amount"));
	foodLayout->addWidget(foodLabel);

	foodAmount_ = new QLabel;
	foodAmount_->setFont(font);
	foodAmount_->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	foodLayout->addWidget(foodAmount_);

	return foodLayout;
}
