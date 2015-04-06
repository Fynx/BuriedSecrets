/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Panels/UnitSection.hpp"

#include "GameObjects/Unit.hpp"
#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
#include "DebugManager/DebugManager.hpp"
#include "UserInterface/Resources.hpp"
#include "UserInterface/Panels/UnitsPanel.hpp"

const QSize UnitSection::AvatarSize{64, 64};
const QSize UnitSection::IconSize{16, 16};
const int UnitSection::BarWidth{10};

UnitSection::UnitSection(const Unit *unit, DataManager *dataManager)
	: unit_(unit),
	  dataManager_(dataManager)
{
	setAutoFillBackground(true);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	setLineWidth(3);
	setFrameStyle(QFrame::Panel | QFrame::Sunken);

	initLayout();
}

const Unit *UnitSection::unit()
{
	return unit_;
}

QSize UnitSection::sizeHint() const
{
	return UnitsPanel::SectionSize;
}

void UnitSection::refresh()
{
	switch(unit_->getAttitude()) {
		case BS::Attitude::BuildingAggressive:
		case BS::Attitude::Aggressive:
			attitudeIcon_->setPixmap(QPixmap(Icons::Aggresive).scaled(IconSize));
			break;
		case BS::Attitude::BuildingDefensive:
		case BS::Attitude::Guard:
			attitudeIcon_->setPixmap(QPixmap(Icons::Guard).scaled(IconSize));
			break;
		case BS::Attitude::Coward:
			attitudeIcon_->setPixmap(QPixmap(Icons::Coward).scaled(IconSize));
			break;
		default:
			err("Unknown attitude");
	}

	if (unit_->getState() == BS::State::Inside)
		locationIcon_->setPixmap(QPixmap(Icons::LocationSelected).scaled(IconSize));
	else
		locationIcon_->setPixmap(QPixmap(Icons::Location).scaled(IconSize));

	if (unit_->property(TempData::NearCamp).toBool())
		campIcon_->setPixmap(QPixmap(Icons::CampSelected).scaled(IconSize));
	else
		campIcon_->setPixmap(QPixmap(Icons::Camp).scaled(IconSize));

	hpBar_->setMaximum(unit_->getMaxHP());
	hpBar_->setValue(unit_->getHP());

	psychosisBar_->setMaximum(unit_->getMaxPsychosis());
	psychosisBar_->setValue(unit_->getPsychosis());
}

void UnitSection::setSelected(bool isSelected)
{
	if (isSelected)
		setFrameStyle(QFrame::Panel | QFrame::Raised);
	else
		setFrameStyle(QFrame::Panel | QFrame::Sunken);
}

void UnitSection::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit showMenu();

	QWidget::mouseDoubleClickEvent(event);
}

void UnitSection::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		emit pickUnit();

	if (event->button() == Qt::RightButton)
		emit showUnit();

	QWidget::mousePressEvent(event);
}

void UnitSection::initLayout()
{
	auto mainLayout = new QVBoxLayout;
	setLayout(mainLayout);

	auto name = new QLabel(unit_->getName());
	name->setFont(QFont("Times", 12));
	name->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(name);

	auto hLayout = new QHBoxLayout;
	hLayout->addLayout(createIconsLayout());
	hLayout->addWidget(createAvatarWidget());
	hLayout->addLayout(createBarsLayout());
	mainLayout->addLayout(hLayout);
}

QLayout *UnitSection::createIconsLayout()
{
	auto iconsLayout = new QVBoxLayout;

	attitudeIcon_ = new QLabel;
	iconsLayout->addWidget(attitudeIcon_);

	campIcon_ = new QLabel;
	iconsLayout->addWidget(campIcon_);

	locationIcon_ = new QLabel;
	iconsLayout->addWidget(locationIcon_);

	return iconsLayout;
}

QWidget *UnitSection::createAvatarWidget()
{
	auto avatar = new QLabel;
	QString avatarName = unit_->getPrototype()->getProperty(Properties::Avatar).toString();
	const Resource *res = dataManager_->getResource(avatarName);
	QImage img;
	img.loadFromData(reinterpret_cast<const uchar *>(res->getData()), res->getDataLength());
	avatar->setPixmap(QPixmap::fromImage(img).scaled(AvatarSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

	return avatar;
}

QLayout *UnitSection::createBarsLayout()
{
	auto barsLayout = new QHBoxLayout;

	hpBar_ = new QProgressBar;
	hpBar_->setTextVisible(false);
	hpBar_->setOrientation(Qt::Vertical);
	hpBar_->setMinimum(0);
	hpBar_->setMaximumWidth(BarWidth);
	barsLayout->addWidget(hpBar_);

	psychosisBar_ = new QProgressBar;
	psychosisBar_->setTextVisible(false);
	psychosisBar_->setOrientation(Qt::Vertical);
	psychosisBar_->setMinimum(0);
	psychosisBar_->setMaximumWidth(BarWidth);
	barsLayout->addWidget(psychosisBar_);

	return barsLayout;
}
