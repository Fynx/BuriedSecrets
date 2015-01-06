/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitsPanel.hpp"

#include "UserInterface/UnitWidget.hpp"

UnitsPanel::UnitsPanel()
{
	setLayout(new QHBoxLayout);
	setAutoFillBackground(true);

	//TMP
	addUnitWidget(new UnitWidget);
	addUnitWidget(new UnitWidget);
	addUnitWidget(new UnitWidget);
	addUnitWidget(new UnitWidget);
	addUnitWidget(new UnitWidget);
	addUnitWidget(new UnitWidget);
}

QSize UnitsPanel::sizeHint() const
{
	if (unitWidgets_.isEmpty())
		return QSize{0,0};

	int totalWidth = unitWidgets_[0]->sizeHint().width() * unitWidgets_.size();\
	int totalHeight = unitWidgets_[0]->sizeHint().height();
	return QSize{totalWidth, totalHeight};
}

void UnitsPanel::addUnitWidget(UnitWidget *unitWidget)
{
	unitWidgets_.append(unitWidget);
	layout()->addWidget(unitWidget);
}
