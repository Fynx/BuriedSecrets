/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "CampPanel.hpp"

#include "Mind/Mind.hpp"

CampPanel::CampPanel()
{
	setAutoFillBackground(true);
	initWidgets();
	initLayout();
}

void CampPanel::update(const Mind *mind)
{
	setFoodAmount(mind->getPlayerFaction()->getFood());
}

void CampPanel::initWidgets()
{
	journalBtn_ = new QPushButton("Journal");
	journalBtn_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(journalBtn_, &QPushButton::clicked, this, &CampPanel::journalActivated);

	campEquipmentBtn_ = new QPushButton("Camp EQ");
	campEquipmentBtn_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(campEquipmentBtn_, &QPushButton::clicked, this, &CampPanel::campEQActivated);

	foodLabel_ = new QLabel;
	setFoodAmount(0);
}

void CampPanel::initLayout()
{
	setLayout(new QHBoxLayout);

	layout()->addWidget(journalBtn_);
	layout()->addWidget(campEquipmentBtn_);
	layout()->addWidget(foodLabel_);
}

void CampPanel::setFoodAmount(int food)
{
	foodLabel_->setText("Food Amount:\n" + QString::number(food));
}
