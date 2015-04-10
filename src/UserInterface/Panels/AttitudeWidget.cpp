/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Panels/AttitudeWidget.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/JournalEntry.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/Resources.hpp"

const QFont AttitudeWidget::TextFont{"Times", 14};
const QSize AttitudeWidget::IconSize{16, 16};
const QSize AttitudeWidget::WidgetSize{160, 130};

AttitudeWidget::AttitudeWidget(Mind *m)
	: mind_(m),
	  outsideAttitudes_(true)
{
	setAutoFillBackground(true);

	initLayout();
	resize(WidgetSize);
	hide();
	connect(&signalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
			this, &AttitudeWidget::onOptionClicked);
}

void AttitudeWidget::refresh(QSet<int> uids)
{
	// see if selection changed
	if (uids != uids_) {
		setUnits(uids);
		return;
	}

	// check if case when one person in selection went in/out
	if (! uids.isEmpty() && anyUnitOutside(uids) != outsideAttitudes_)
		setUnits(uids);
}

void AttitudeWidget::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	auto label = new QLabel(tr("Behaviour"));
	label->setAlignment(Qt::AlignCenter);
	label->setFont(TextFont);
	layout->addWidget(label);

	attitudeLayout_ = new QVBoxLayout;
	layout->addLayout(attitudeLayout_);
}

void AttitudeWidget::setUnits(QSet<int> uids)
{
	uids_ = uids;
	clearOptions();

	if (uids.isEmpty() || ! inSameLocation(uids)) {
		hide();
		return;
	}
	else
		show();

	if (anyUnitOutside(uids)) {
		outsideAttitudes_ = true;
		addOption(BS::Attitude::Aggressive);
		addOption(BS::Attitude::Guard);
	}
	else {
		outsideAttitudes_ = false;
		addOption(BS::Attitude::BuildingAggressive);
		addOption(BS::Attitude::BuildingDefensive);
	}
}

bool AttitudeWidget::inSameLocation(QSet<int> uids)
{
	int numInside;
	int numOutside;

	for (int uid : uids) {
		auto unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
		if (unit->getState() == BS::State::Inside)
			++numInside;
		else
			++ numOutside;
	}

	return numInside != 0 && numOutside != 0;
}

bool AttitudeWidget::anyUnitOutside(QSet<int> uids)
{
	if (uids.isEmpty())
		return true;
	auto unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(*(uids.begin())));
	return unit->getState() != BS::State::Inside;
}

void AttitudeWidget::addOption(BS::Attitude option)
{
	QPixmap icon;
	QString text;
	switch (option) {
		case BS::Attitude::BuildingAggressive:
		case BS::Attitude::Aggressive:
			icon = QPixmap(Icons::Aggresive).scaled(IconSize);
			text = tr("Aggresive");
			break;
		case BS::Attitude::BuildingDefensive:
		case BS::Attitude::Guard:
			icon = QPixmap(Icons::Guard).scaled(IconSize);
			text = tr("Guard");
			break;
		default:
			err("Unknown attitude");
	}

	auto btn = new QPushButton(icon, text);
	btn->setFont(TextFont);
	connect(btn, &QPushButton::clicked,
			&signalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	signalMapper_.setMapping(btn, options_.count());
	options_.append(option);
	attitudeLayout_->addWidget(btn);
}

void AttitudeWidget::clearOptions()
{
	while (QLayoutItem *child = attitudeLayout_->takeAt(0)) {
		delete child->widget();
		delete child;
	}

	options_.clear();
}

void AttitudeWidget::onOptionClicked(int option)
{
	for (int uid : uids_) {
		auto unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
		unit->setAttitude(options_[option]);
	}
}
