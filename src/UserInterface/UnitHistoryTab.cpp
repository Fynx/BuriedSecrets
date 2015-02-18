/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitHistoryTab.hpp"

#include "GameObjects/Unit.hpp"

UnitHistoryTab::UnitHistoryTab(Unit *unit) : unit_(unit)
{
	initLayout();
}

void UnitHistoryTab::initLayout()
{
	QFormLayout *mainLayout = new QFormLayout;
	setLayout(mainLayout);

	mainLayout->addRow(new QLabel("<picture goes here>"));
	mainLayout->addRow("Name",       new QLabel(unit_->getName()));
	mainLayout->addRow("Age",        new QLabel("<age goes here>"));
	mainLayout->addRow("Rank",       new QLabel("<rank goes here>"));
	mainLayout->addRow("Background", new QLabel("<background goes here>"));
}
