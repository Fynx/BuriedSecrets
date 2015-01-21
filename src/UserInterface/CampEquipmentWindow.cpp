/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "CampEquipmentWindow.hpp"

CampEquipmentWindow::CampEquipmentWindow()
{
	closeBtn_ = new QPushButton("Close");
	connect (closeBtn_, &QPushButton::clicked, this, &CampEquipmentWindow::exit);

	setAutoFillBackground(true);

	initLayout();
}

void CampEquipmentWindow::initLayout()
{
	QVBoxLayout *layout  = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(new QLabel("Camp Equipment"));
	layout->addStretch();
	layout->addWidget(closeBtn_);
}
