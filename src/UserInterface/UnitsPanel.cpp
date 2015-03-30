/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/UnitsPanel.hpp"

#include "Mind/Mind.hpp"
#include "GameObjects/Unit.hpp"
#include "UserInterface/DeadSection.hpp"
#include "UserInterface/UnitSection.hpp"

const QSize UnitsPanel::SectionSize{160, 130};

UnitsPanel::UnitsPanel(DataManager *dataManager, const Mind *mind)
	: dataManager_(dataManager),
	  mind_(mind)
{
	setAutoFillBackground(true);

	panelLayout_  = new QHBoxLayout;
	setLayout(panelLayout_);

	connect(&pickSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
	        this, &UnitsPanel::pickUnit);
	connect(&showMenuSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
	        this, &UnitsPanel::showUnitMenu);
	connect(&showUnitSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
	        this, &UnitsPanel::showUnit);
}

QSize UnitsPanel::sizeHint() const
{
	if (panelLayout_->count() == 0)
		return QSize{0, SectionSize.height()};

	return QSize{SectionSize.width() * panelLayout_->count(), SectionSize.height()};
}

void UnitsPanel::refresh()
{
	if (didUnitsChange()) {
		rebuild();
		emit sizeChanged();
	}

	for (auto &iter : unitSections_)
		iter->refresh();
}

bool UnitsPanel::didUnitsChange()
{
	QList<int> allUnits = mind_->getPlayerFaction()->getAllUnitsUids();

	if (allUnits.size() != unitsStates_.size())
		return true;

	for (int i = 0; i < allUnits.size(); ++i) {
		// check uid
		if (allUnits[i] != unitsStates_[i].first)
			return true;
		//check state
		if (mind_->getPlayerFaction()->isAliveMember(allUnits[i]) != unitsStates_[i].second)
			return true;
	}
	return false;
}

void UnitsPanel::rebuild()
{
	unitsStates_.clear();
	unitSections_.clear();

	QLayoutItem *child;
	while ((child = panelLayout_->takeAt(0)) != nullptr)
		delete child;

	auto faction = mind_->getPlayerFaction();

	for (int uid : faction->getAllUnitsUids()) {
		unitsStates_.append({uid, faction->isAliveMember(uid)});
		if (unitsStates_.back().second)
			appendUnitSection(uid);
		else {
			panelLayout_->addWidget(new DeadSection);
		}
	}
}

void UnitsPanel::appendUnitSection(int uid)
{
	const Unit *unit = dynamic_cast<const Unit *>(mind_->getObjectFromUid(uid));
	UnitSection *unitSection = new UnitSection(unit, dataManager_);

	unitSections_.insert(unitSection);
	panelLayout_->addWidget(unitSection);

	connect(unitSection, &UnitSection::pickUnit,
	        &pickSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	connect(unitSection, &UnitSection::showMenu,
			&showMenuSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	connect(unitSection, &UnitSection::showUnit,
			&showUnitSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

	pickSignalMapper_.setMapping(unitSection, unitSection->unit()->getUid());
	showMenuSignalMapper_.setMapping(unitSection, unitSection->unit()->getUid());
	showUnitSignalMapper_.setMapping(unitSection, unitSection->unit()->getUid());
}
