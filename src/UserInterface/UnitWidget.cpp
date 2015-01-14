/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitWidget.hpp"

#include "GameObjects/Unit.hpp"

UnitWidget::UnitWidget(const Unit *unit) : unit_(unit)
{
	setAutoFillBackground(true);
	setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	initWidgets();
	initLayout();
}

QSize UnitWidget::sizeHint() const
{
	return WidgetSize;
}

void UnitWidget::refresh()
{
	hpBar_->setMaximum(unit_->getMaxHP());
	hpBar_->setValue(unit_->getHP());

	psychosisBar_->setMaximum(unit_->getMaxPsychosis());
	psychosisBar_->setValue(unit_->getPsychosis());

	encumbranceBar_->setMaximum(unit_->getMaxEncumbrance());
	encumbranceBar_->setValue(unit_->getEncumbrance());

	behaviourLabel_->setText("Defensive");
}

void UnitWidget::initWidgets()
{
	locationIcon_ = new QFrame;

	campIcon_ = new QFrame;


	name_ = new QLabel(unit_->getName());

	face_ = new QPushButton("Face");
	face_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


	hpBar_ = new QProgressBar;
	hpBar_->setFormat("%v/%m");
	hpBar_->setMinimum(0);

	psychosisBar_ = new QProgressBar;
	psychosisBar_->setFormat("%v/%m");
	psychosisBar_->setMinimum(0);

	encumbranceBar_ = new QProgressBar;
	encumbranceBar_->setFormat("%v/%m");
	encumbranceBar_->setMinimum(0);

	behaviourLabel_ = new QLabel;
}

void UnitWidget::initLayout()
{
	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addWidget(locationIcon_);
	leftLayout->addWidget(campIcon_);

	QVBoxLayout *middleLayout = new QVBoxLayout;
	middleLayout->addWidget(face_);
	middleLayout->addWidget(name_);

	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(hpBar_);
	rightLayout->addWidget(psychosisBar_);
	rightLayout->addWidget(encumbranceBar_);
	rightLayout->addWidget(behaviourLabel_);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	setLayout(mainLayout);
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(middleLayout);
	mainLayout->addLayout(rightLayout);
}
