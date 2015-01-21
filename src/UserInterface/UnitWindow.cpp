/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UnitWindow.hpp"

#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

UnitWindow::UnitWindow(Mind *mind) : mind_(mind), unit_(nullptr)
{
	closeBtn_ = new QPushButton("Close");
	connect (closeBtn_, &QPushButton::clicked, this, &UnitWindow::exit);

	title_ = new QLabel;
	setAutoFillBackground(true);

	initLayout();
}

void UnitWindow::initLayout()
{
	QVBoxLayout *layout  = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(title_);
	layout->addStretch();
	layout->addWidget(closeBtn_);
}

void UnitWindow::setUnit(int uid)
{
	Unit *unit_ = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));

	title_->setText(unit_->getName());
}
