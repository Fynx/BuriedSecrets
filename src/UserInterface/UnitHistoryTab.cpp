/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitHistoryTab.hpp"

#include "DataManager/DataManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Common/Strings.hpp"

const QSize UnitHistoryTab::PictureSize{256, 256};
const QMargins UnitHistoryTab::ContentsMargins{32, 32, 32, 32};

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

QWidget* UnitHistoryTab::createPictureWidget()
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

QLayout* UnitHistoryTab::createDataLayout()
{
	QFormLayout *layout = new QFormLayout;
	layout->setVerticalSpacing(VerticalSpacing);
	layout->setHorizontalSpacing(HorizontalSpacing);

	layout->addRow(keyLabel(tr("Name")), valueLabel(unit_->getName()));

	int age = unit_->getPrototype()->getProperty(Properties::Age).toInt();
	layout->addRow(keyLabel(tr("Age")), valueLabel(QString::number(age)));

	QString profession = unit_->getPrototype()->getProperty(Properties::Profession).toString();
	layout->addRow(keyLabel(tr("Profession")), valueLabel(profession));

	QString background = unit_->getPrototype()->getProperty(Properties::Background).toString();
	layout->addRow(keyLabel(tr("Background")), valueLabel(background));

	QString quote = unit_->getPrototype()->getProperty(Properties::Quote).toString();
	layout->addRow(keyLabel(tr("Quote")), valueLabel(quote));

	return layout;
}

QLabel *UnitHistoryTab::keyLabel(const QString &title)
{
	auto label = new QLabel(title);
	label->setFont(QFont("Arial", 16, QFont::Bold));
	return label;
}

QLabel *UnitHistoryTab::valueLabel(const QString &value)
{
	auto label = new QLabel(value);
	label->setWordWrap(true);
	label->setFont(QFont("Times", 16));
	return label;
}
