/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitsPanel.hpp"

#include "UserInterface/UnitWidget.hpp"
#include "Mind/Mind.hpp"

UnitsPanel::UnitsPanel()
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
	if (unitWidgets_.isEmpty())
		return QSize{0, UnitWidget::WidgetSize.height()};

	int totalWidth = unitWidgets_[0]->sizeHint().width() * unitWidgets_.size();
	int totalHeight = unitWidgets_[0]->sizeHint().height();
	return QSize{totalWidth, totalHeight};
}

void UnitsPanel::refresh(const Mind *mind)
{
	QList <int> allUnits = mind->getPlayerFaction()->getAllUnitsUids();

	//check if there are new units
	int iter = unitWidgets_.size();

	if (iter < allUnits.size()) {
		while (iter < allUnits.size()) {
			const Unit *unit = dynamic_cast<const Unit *>(mind->getObjectFromUid(allUnits[iter]));
			UnitWidget *unitWidget = new UnitWidget(unit);

			addUnitWidget(unitWidget);
			++iter;
		}
		emit sizeChanged();
	}

	for (auto &iter : unitWidgets_)
		iter->refresh();
}

void UnitsPanel::addUnitWidget(UnitWidget *unitWidget)
{
	unitWidgets_.append(unitWidget);
	layout()->addWidget(unitWidget);

	connect(unitWidget, &UnitWidget::add,
	        &addSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	connect(unitWidget, &UnitWidget::heal,
			&healSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	connect(unitWidget, &UnitWidget::select,
	        &selectSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	connect(unitWidget, &UnitWidget::showMenu,
			&showMenuSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	connect(unitWidget, &UnitWidget::showUnit,
			&showUnitSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

	addSignalMapper_.setMapping(unitWidget, unitWidget->unit()->getUid());
	healSignalMapper_.setMapping(unitWidget, unitWidget->unit()->getUid());
	selectSignalMapper_.setMapping(unitWidget, unitWidget->unit()->getUid());
	showMenuSignalMapper_.setMapping(unitWidget, unitWidget->unit()->getUid());
	showUnitSignalMapper_.setMapping(unitWidget, unitWidget->unit()->getUid());

}
