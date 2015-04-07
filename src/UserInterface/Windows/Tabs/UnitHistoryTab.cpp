/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/Tabs/UnitHistoryTab.hpp"

#include "DataManager/DataManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Common/Strings.hpp"

const QSize UnitHistoryTab::PictureSize{256, 256};
const QMargins UnitHistoryTab::ContentsMargins{15, 15, 15, 15};

UnitHistoryTab::UnitHistoryTab(Unit *unit, DataManager *dataManager)
	: unit_(unit),
	  dataManager_(dataManager)
{
	setContentsMargins(ContentsMargins);
	initLayout();
}

void UnitHistoryTab::initLayout()
{
	auto mainLayout = new QVBoxLayout;
	setLayout(mainLayout);

	mainLayout->addWidget(createPictureWidget());
	mainLayout->addLayout(createDataLayout());
}

QWidget *UnitHistoryTab::createPictureWidget()
{
	auto picture = new QLabel;
	QString avatarName = unit_->getPrototype()->getProperty(Properties::Picture).toString();
	const Resource *res = dataManager_->getResource(avatarName);
	QImage img;
	img.loadFromData(reinterpret_cast<const uchar *>(res->getData()), res->getDataLength());
	QPixmap pixmap(QPixmap::fromImage(img).scaled(PictureSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	picture->setPixmap(pixmap);
	picture->setAlignment(Qt::AlignCenter);

	return picture;
}

QLayout *UnitHistoryTab::createDataLayout()
{
	auto layout = new QGridLayout;
// 	layout->setHorizontalSpacing(HorizontalSpacing);

	auto layoutUp = new QFormLayout;
	layout->addLayout(layoutUp, 0, 0, 1, 2);
	layoutUp->setVerticalSpacing(VerticalSpacing);
	layoutUp->setHorizontalSpacing(HorizontalSpacing);

	layoutUp->addRow(keyLabel(tr("Name")), valueLabel(unit_->getName()));

	QString label;
	// History
	label = unit_->getPrototype()->getProperty(Properties::Age).toString();
	layoutUp->addRow(keyLabel(tr("Age")), valueLabel(label));

	label = unit_->getPrototype()->getProperty(Properties::Profession).toString();
	layoutUp->addRow(keyLabel(tr("Profession")), valueLabel(label));

	label = unit_->getPrototype()->getProperty(Properties::Background).toString();
	layoutUp->addRow(keyLabel(tr("Background")), valueLabel(label));

	label = unit_->getPrototype()->getProperty(Properties::Quote).toString();
	layoutUp->addRow(keyLabel(tr("Quote")), valueLabel(label));

	auto statsLeft = new QFormLayout;
	layout->addLayout(statsLeft, 1, 0, 1, 1);
	statsLeft->setVerticalSpacing(VerticalSpacing);
	statsLeft->setHorizontalSpacing(HorizontalSpacing);

	// Basic stats
	label = unit_->getPrototype()->getProperty(Properties::Encumbrance).toString();
	statsLeft->addRow(keyLabel(tr("Encumbrance")), valueLabel(label));

	label = unit_->getPrototype()->getProperty(Properties::FoodDemand).toString();
	statsLeft->addRow(keyLabel(tr("Food demand")), valueLabel(label));

	label = unit_->getPrototype()->getProperty(Properties::HP).toString();
	statsLeft->addRow(keyLabel(tr("Phisical health")), valueLabel(label));

	label = unit_->getPrototype()->getProperty(Properties::Psychosis).toString();
	statsLeft->addRow(keyLabel(tr("Mental health")), valueLabel(label));

	label = unit_->getPrototype()->getProperty(Properties::Regeneration).toString();
	statsLeft->addRow(keyLabel(tr("Regeneration")), valueLabel(label));

	auto statsRight = new QFormLayout;
	layout->addLayout(statsRight, 1, 1, 1, 1);
	statsRight->setVerticalSpacing(VerticalSpacing);
	statsRight->setHorizontalSpacing(HorizontalSpacing);

	// Skill stats
	label = unit_->getPrototype()->getProperty(Properties::Engineering).toString();
	statsRight->addRow(keyLabel(tr("Engineering")), valueLabel(label));

	label = unit_->getPrototype()->getProperty(Properties::Healing).toString();
	statsRight->addRow(keyLabel(tr("Healing")), valueLabel(label));
	/*
	label = unit_->getPrototype()->getProperty(Properties::Perception).toString();
	statsRight->addRow(keyLabel(tr("Perception")), valueLabel(label));
	*/
	label = unit_->getPrototype()->getProperty(Properties::DamageControl).toString();
	statsRight->addRow(keyLabel(tr("Damage control")), valueLabel(label));

	label = unit_->getPrototype()->getProperty(Properties::SightRange).toString();
	statsRight->addRow(keyLabel(tr("Sight range")), valueLabel(label));

	label = unit_->getPrototype()->getProperty(Properties::MovementSpeed).toString();
	statsRight->addRow(keyLabel(tr("Movement speed")), valueLabel(label));

	return layout;
}

QLabel *UnitHistoryTab::keyLabel(const QString &title)
{
	auto label = new QLabel(title);
	label->setFont(QFont("Arial", 14, QFont::Bold));
	return label;
}

QLabel *UnitHistoryTab::valueLabel(const QString &value)
{
	auto label = new QLabel(value);
	label->setWordWrap(true);
	label->setFont(QFont("Times", 14));
	return label;
}
