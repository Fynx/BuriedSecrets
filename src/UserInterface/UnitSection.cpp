/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitSection.hpp"

#include "GameObjects/Unit.hpp"
#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
#include "UserInterface/UnitsPanel.hpp"

const QSize UnitSection::AvatarSize{64, 64};

UnitSection::UnitSection(const Unit *unit, DataManager *dataManager)
	: unit_(unit),
	  dataManager_(dataManager)
{
	setAutoFillBackground(true);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	setLineWidth(3);

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
	hpBar_->setMaximum(unit_->getMaxHP());
	hpBar_->setValue(unit_->getHP());

	psychosisBar_->setMaximum(unit_->getMaxPsychosis());
	psychosisBar_->setValue(unit_->getPsychosis());

	if (unit_->property(TempData::IsSelected).toBool())
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
	emit pickUnit();

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
	hLayout->addWidget(createAvatarWidget());
	hLayout->addLayout(createBarsLayout());
	hLayout->addLayout(createIconsLayout());
	mainLayout->addLayout(hLayout);
}

QLayout *UnitSection::createIconsLayout()
{
	auto iconsLayout = new QVBoxLayout;

	auto locationIcon = new QFrame;
	iconsLayout->addWidget(locationIcon);

	auto campIcon = new QFrame;
	iconsLayout->addWidget(campIcon);

	auto behaviourIcon = new QFrame;
	iconsLayout->addWidget(behaviourIcon);

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
	barsLayout->addWidget(hpBar_);

	psychosisBar_ = new QProgressBar;
	psychosisBar_->setTextVisible(false);
	psychosisBar_->setOrientation(Qt::Vertical);
	psychosisBar_->setMinimum(0);
	barsLayout->addWidget(psychosisBar_);

	return barsLayout;
}
