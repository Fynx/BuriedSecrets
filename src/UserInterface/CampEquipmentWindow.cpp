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

QWidget *CampEquipmentWindow::createTabWidget()
{
	tabWidget_ = new QTabWidget;
	tabWidget_->setTabShape(QTabWidget::Triangular);

	equipmentTab_ = new QWidget;
	constructorTab_ = new QWidget;

	tabWidget_->addTab(equipmentTab_, "Equipment");
	tabWidget_->addTab(constructorTab_, "Stats");

	return tabWidget_;
}

void CampEquipmentWindow::initLayout()
{
	QVBoxLayout *layout  = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(new QLabel("Camp Equipment"));
	layout->addStretch();
	layout->addWidget(closeBtn_);
}
