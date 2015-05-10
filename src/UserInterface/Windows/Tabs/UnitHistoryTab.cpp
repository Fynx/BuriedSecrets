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
	QVBoxLayout *mainLayout = new QVBoxLayout;
	setLayout(mainLayout);

	mainLayout->addWidget(createPictureWidget());
	mainLayout->addLayout(createDataLayout());
}

QWidget *UnitHistoryTab::createPictureWidget()
{
	QLabel *picture = new QLabel;
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
	QGridLayout *layout = new QGridLayout;
// 	layout->setHorizontalSpacing(HorizontalSpacing);

	QFormLayout *layoutUp = new QFormLayout;
	layout->addLayout(layoutUp, 0, 0, 1, 2);
	layoutUp->setVerticalSpacing(VerticalSpacing);
	layoutUp->setHorizontalSpacing(HorizontalSpacing);

	// History
	addProperty(tr("Name"),       Properties::Name,       layoutUp);
	addProperty(tr("Age"),        Properties::Age,        layoutUp);
	addProperty(tr("Profession"), Properties::Profession, layoutUp);
	addProperty(tr("Background"), Properties::Background, layoutUp);
	addProperty(tr("Quote"),      Properties::Quote,      layoutUp);

	QFormLayout *statsLeft = new QFormLayout;
	layout->addLayout(statsLeft, 1, 0, 1, 1);
	statsLeft->setVerticalSpacing(VerticalSpacing);
	statsLeft->setHorizontalSpacing(HorizontalSpacing);

	// Basic stats
	addProperty(tr("Encumbrance"),     Properties::Encumbrance,  statsLeft);
	addProperty(tr("Food demand"),     Properties::FoodDemand,   statsLeft);
	addProperty(tr("Physical health"), Properties::HP,           statsLeft);
	addProperty(tr("Mental health"),   Properties::Psychosis,    statsLeft);
	addProperty(tr("Regeneration"),    Properties::Regeneration, statsLeft);

	QFormLayout *statsRight = new QFormLayout;
	layout->addLayout(statsRight, 1, 1, 1, 1);
	statsRight->setVerticalSpacing(VerticalSpacing);
	statsRight->setHorizontalSpacing(HorizontalSpacing);

	// Skill stats
// 	addProperty(tr("Engineering"),    Properties::Engineering,   statsRight);
	addProperty(tr("Healing"),        Properties::Healing,       statsRight);
// 	addProperty(tr("Perception"),     Properties::Perception,    statsRight);
	addProperty(tr("Damage control"), Properties::DamageControl, statsRight);
	addProperty(tr("Sight range"),    Properties::SightRange,    statsRight);
	addProperty(tr("Movent speed"),   Properties::MovementSpeed, statsRight);

	return layout;
}

void UnitHistoryTab::addProperty(const QString &key, const QString &property, QFormLayout *layout)
{
	QLabel *labelKey = new QLabel(key);
	labelKey->setFont(QFont("Arial", 14, QFont::Bold));

	QString valueTxt = unit_->getPrototype()->getProperty(property).toString();
	QLabel *labelValue = new QLabel(valueTxt);
	labelValue->setWordWrap(true);
	labelValue->setFont(QFont("Times", 14));

	layout->addRow(labelKey, labelValue);
}
