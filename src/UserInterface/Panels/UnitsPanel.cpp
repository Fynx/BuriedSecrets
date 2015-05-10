/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Panels/UnitsPanel.hpp"

#include "Mind/Mind.hpp"
#include "GameObjects/Unit.hpp"
#include "UserInterface/Panels/IconSection.hpp"
#include "UserInterface/Panels/UnitSection.hpp"
#include "UserInterface/Resources.hpp"

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

void UnitsPanel::setSelection(int uid, bool isSelected)
{
	unitSections_[uid]->setSelected(isSelected);
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
		if (determineUnitStatus(allUnits[i]) != unitsStates_[i].second)
			return true;
	}
	return false;
}

void UnitsPanel::rebuild()
{
	unitsStates_.clear();
	unitSections_.clear();

	while (QLayoutItem *child = panelLayout_->takeAt(0)) {
		delete child->widget();
		delete child;
	}

	for (int uid : mind_->getPlayerFaction()->getAllUnitsUids()) {
		auto state = determineUnitStatus(uid);
		unitsStates_.append({uid, state});

		switch (state) {
		case UnitStatus::Member:
			appendUnitSection(uid);
			break;
		case UnitStatus::Psycho:
			panelLayout_->addWidget(new IconSection(Icons::Psycho));
			break;
		case UnitStatus::Dead:
			panelLayout_->addWidget(new IconSection(Icons::Skull));
			break;
		}
	}
}

void UnitsPanel::appendUnitSection(int uid)
{
	const Unit *unit = mind_->getUnit(uid);
	UnitSection *unitSection = new UnitSection(unit, dataManager_);

	unitSections_.insert(uid, unitSection);
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

UnitStatus UnitsPanel::determineUnitStatus(int uid)
{
	if (mind_->getPlayerFaction()->isAliveMember(uid))
		return UnitStatus::Member;

	if (mind_->isNotRemoved(uid))
		return UnitStatus::Psycho;

	return UnitStatus::Dead;
}
