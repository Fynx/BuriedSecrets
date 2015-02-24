/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitsPanel.hpp"

#include "UserInterface/UnitSection.hpp"
#include "Mind/Mind.hpp"

UnitsPanel::UnitsPanel(DataManager *dataManager) : dataManager_(dataManager)
{
	setLayout(new QHBoxLayout);
	setAutoFillBackground(true);
	connect(&addSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
	        this, &UnitsPanel::addUnit);
	connect(&healSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
	        this, &UnitsPanel::healUnit);
	connect(&selectSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
	        this, &UnitsPanel::selectUnit);
	connect(&showMenuSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
	        this, &UnitsPanel::showUnitMenu);
	connect(&showUnitSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
	        this, &UnitsPanel::showUnit);
}

QSize UnitsPanel::sizeHint() const
{
	if (unitSections_.isEmpty())
		return QSize{0, UnitSection::WidgetSize.height()};

	int totalWidth = unitSections_[0]->sizeHint().width() * unitSections_.size();
	int totalHeight = unitSections_[0]->sizeHint().height();
	return QSize{totalWidth, totalHeight};
}

void UnitsPanel::refresh(const Mind *mind)
{
	QList <int> allUnits = mind->getPlayerFaction()->getAllUnitsUids();

	//check if there are new units
	int iter = unitSections_.size();

	if (iter < allUnits.size()) {
		while (iter < allUnits.size()) {
			const Unit *unit = dynamic_cast<const Unit *>(mind->getObjectFromUid(allUnits[iter]));
			UnitSection *unitWidget = new UnitSection(unit, dataManager_);

			addUnitSection(unitWidget);
			++iter;
		}
		emit sizeChanged();
	}

	for (auto &iter : unitSections_)
		iter->refresh();
}

void UnitsPanel::addUnitSection(UnitSection *unitSection)
{
	unitSections_.append(unitSection);
	layout()->addWidget(unitSection);

	connect(unitSection, &UnitSection::add,
	        &addSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	connect(unitSection, &UnitSection::heal,
			&healSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	connect(unitSection, &UnitSection::select,
	        &selectSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	connect(unitSection, &UnitSection::showMenu,
			&showMenuSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	connect(unitSection, &UnitSection::showUnit,
			&showUnitSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

	addSignalMapper_.setMapping(unitSection, unitSection->unit()->getUid());
	healSignalMapper_.setMapping(unitSection, unitSection->unit()->getUid());
	selectSignalMapper_.setMapping(unitSection, unitSection->unit()->getUid());
	showMenuSignalMapper_.setMapping(unitSection, unitSection->unit()->getUid());
	showUnitSignalMapper_.setMapping(unitSection, unitSection->unit()->getUid());

}
