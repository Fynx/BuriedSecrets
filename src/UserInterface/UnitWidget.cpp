/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitWidget.hpp"

#include "GameObjects/Unit.hpp"
#include "Common/Strings.hpp"

UnitWidget::UnitWidget(const Unit *unit) : unit_(unit)
{
	setAutoFillBackground(true);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	setLineWidth(3);

	initWidgets();
	initLayout();
}

const Unit *UnitWidget::unit()
{
	return unit_;
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

	if (unit_->property(Properties::IsSelected).toBool())
		setFrameStyle(QFrame::Panel | QFrame::Raised);
	else
		setFrameStyle(QFrame::Panel | QFrame::Sunken);
}

void UnitWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit showMenu();

	QWidget::mouseDoubleClickEvent(event);
}

void UnitWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		if (QApplication::keyboardModifiers() & Qt::ControlModifier)
			emit added();
		else
			emit selected();
	}
	if (event->button() == Qt::RightButton) {
		if (QApplication::keyboardModifiers() & Qt::AltModifier)
			emit heal();
		else
			emit showUnit();
	}

	QWidget::mousePressEvent(event);
}

void UnitWidget::initWidgets()
{
	locationIcon_ = new QFrame;

	campIcon_ = new QFrame;


	name_ = new QLabel(unit_->getName());

	face_ = new QFrame;
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
	middleLayout->addWidget(name_);
	middleLayout->addWidget(face_);

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
