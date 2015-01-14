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
}

QSize UnitsPanel::sizeHint() const
{
	if (unitWidgets_.isEmpty())
		return QSize{0,0};

	int totalWidth = unitWidgets_[0]->sizeHint().width() * unitWidgets_.size();
	int totalHeight = unitWidgets_[0]->sizeHint().height();
	return QSize{totalWidth, totalHeight};
}

void UnitsPanel::refresh(const Mind *mind)
{
	QList <int> allUnitsUids = mind->getPlayerFaction()->getAllUnits();

	//check if there are new units
	int iter = unitWidgets_.size();

	if (iter < allUnitsUids.size()) {
		while (iter < allUnitsUids.size()) {
			const Unit *unit = dynamic_cast<const Unit *>(mind->getObjectFromUid(allUnitsUids[iter]));
			UnitWidget *uw = new UnitWidget(unit);
			unitWidgets_.append(uw);
			layout()->addWidget(uw);
			++iter;
		}
		emit sizeChanged();
	}

	for (auto &iter : unitWidgets_)
		iter->refresh();
}
