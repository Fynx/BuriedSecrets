
/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/Tabs/Item/ItemWidget.hpp"

#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
#include "GameObjects/Item.hpp"
#include "UserInterface/Resources.hpp"

const QSize ItemWidget::PictureSize{200, 200};
const QSize ItemWidget::StarSize{30, 30};
const QMargins ItemWidget::DetailsContentMargins{0, 0, 0, 0};
const QFont ItemWidget::DetailsFont{"Times", 14};
const QFont ItemWidget::TitlesFont{"Arial", 14, QFont::Bold};


ItemWidget::ItemWidget(DataManager *dataManager) : prototype_(nullptr), dataManager_(dataManager)
{
	setAutoFillBackground(true);

	initLayout();
}

const Prototype *ItemWidget::prototype() const
{
	return prototype_;
}

void ItemWidget::setItem(const Item *item)
{
	prototype_ = item->getPrototype();

	fillWidget();
}

void ItemWidget::setPrototype(const Prototype *prototype)
{
	prototype_ = prototype;

	fillWidget();
}

void ItemWidget::clear()
{
	prototype_ = nullptr;

	layout_->setCurrentIndex(EmptyIndex);
}

void ItemWidget::initLayout()
{
	layout_ = new QStackedLayout;
	setLayout(layout_);

	auto empty = new QLabel(tr("No items"));
	empty->setFont(QFont("Times", 24));
	empty->setAlignment(Qt::AlignCenter);
	layout_->insertWidget(EmptyIndex, empty);

	auto filled = new QWidget;
	auto hLayout = new QHBoxLayout;
	filled->setLayout(hLayout);
	hLayout->addLayout(createMainPart(), 1);
	hLayout->addLayout(createDetailsPart(), 2);
	layout_->insertWidget(FilledIndex, filled);

	layout_->setCurrentIndex(EmptyIndex);
}

QLayout *ItemWidget::createMainPart()
{
	auto layout = new QVBoxLayout;

	pictureLabel_ = new QLabel;
	pictureLabel_->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	layout->addWidget(pictureLabel_);

	nameLabel_ = new QLabel;
	nameLabel_->setFont(QFont("Times", 22));
	nameLabel_->setAlignment(Qt::AlignCenter);
	layout->addWidget(nameLabel_);

	return layout;
}

QLayout *ItemWidget::createDetailsPart()
{
	auto layout = new QVBoxLayout;

	auto fLayout = new QFormLayout;
	layout->addLayout(fLayout);

	fLayout->setContentsMargins(DetailsContentMargins);
	fLayout->setVerticalSpacing(VerticalSpacing);
	fLayout->setHorizontalSpacing(HorizontalSpacing);

	descriptionLabel_ = new QLabel;
	descriptionLabel_->setFont(DetailsFont);
	descriptionLabel_->setWordWrap(true);
	fLayout->addRow(descriptionLabel_);

	auto itemTypeTitle = new QLabel(tr("Type"));
	itemTypeTitle->setFont(TitlesFont);
	itemTypeLabel_ = new QLabel;
	itemTypeLabel_->setFont(DetailsFont);
	fLayout->addRow(itemTypeTitle, itemTypeLabel_);

	auto qualityTitle = new QLabel(tr("Quality"));
	qualityTitle->setFont(TitlesFont);
	auto starsLayout = new QHBoxLayout;
	for (int i = 0; i < Item::StarLimit; ++i) {
		stars_.append(new QLabel);
		starsLayout->addWidget(stars_.back());
	}
	starsLayout->addStretch();
	fLayout->addRow(qualityTitle, starsLayout);

	auto weightTitle = new QLabel(tr("Weight"));
	weightTitle->setFont(TitlesFont);
	weightLabel_ = new QLabel;
	weightLabel_->setFont(DetailsFont);
	fLayout->addRow(weightTitle, weightLabel_);

	layout->addSpacing(VerticalSpacing * 2);

	specificsLayout_ = new QFormLayout;
	specificsLayout_->setContentsMargins(DetailsContentMargins);
	specificsLayout_->setVerticalSpacing(VerticalSpacing);
	specificsLayout_->setHorizontalSpacing(HorizontalSpacing);
	layout->addLayout(specificsLayout_);

	layout->addStretch();

	return layout;
}

void ItemWidget::fillWidget()
{
	layout_->setCurrentIndex(FilledIndex);

	QString pictureName = prototype_->getProperty(Properties::Picture).toString();
	const Resource *res = dataManager_->getResource(pictureName);
	QImage img;
	img.loadFromData(reinterpret_cast<const uchar *>(res->getData()), res->getDataLength());
	QPixmap pixmap(QPixmap::fromImage(img).scaled(PictureSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	pictureLabel_->setPixmap(pixmap);

	nameLabel_->setText(prototype_->getProperty(Properties::Name).toString());

	// Details
	descriptionLabel_->setText(prototype_->getProperty(Properties::Description).toString());
	weightLabel_->setNum(prototype_->getProperty(Properties::Weight).toInt());
	fillQuality(prototype_->getProperty(Properties::Quality).toInt());

	QString itemTypesString;
	for (const QVariant &val : prototype_->getProperty(Properties::ItemTypes).toList()) {
		if (!itemTypesString.isEmpty())
			itemTypesString += ", ";
		itemTypesString += val.toString();
	}
	itemTypeLabel_->setText(itemTypesString);

	fillSpecifics();

	this->repaint();
}

void ItemWidget::fillQuality(int q)
{
	for (int i = 0; i < Item::StarLimit; ++i) {
		if (i < q)
			stars_[i]->setPixmap(QPixmap(Icons::Star).scaled(StarSize));
		else
			stars_[i]->clear();
	}
}

void ItemWidget::fillSpecifics()
{
	while (QLayoutItem *child = specificsLayout_->takeAt(0)) {
		delete child->widget();
		delete child;
	}

	auto components = prototype_->getProperty(Properties::Ingredients).toStringList();
	if (components.count() > 0)
		addSpecific(tr("Parts"), components.join(", "));

	for (auto type : prototype_->getProperty(Properties::ItemTypes).toList()) {
		switch (BS::getCorrespondingSlot(BS::changeStringToItemType(type.toString()))) {
			case BS::Armor:
				addSpecificProperty(tr("Defense"), Properties::Defense);
				break;
			case BS::Medicament:
				addSpecificProperty(tr("Healing"), Properties::Healing);
				break;
			case BS::Tool:
				addSpecificProperty(tr("Engineering"), Properties::Engineering);
				break;
			case BS::Weapon:
				addSpecificProperty(tr("Damage"), Properties::Damage);
				addSpecificProperty(tr("Dispersion"), Properties::Dispersion);
				addSpecificProperty(tr("Range"), Properties::Range);
				addSpecificProperty(tr("Optimal range"), Properties::OptimalRange);
				addSpecificProperty(tr("Shots interval"), Properties::ShotsInterval);
				addSpecificProperty(tr("Magazine size"), Properties::MagazineSize);
				addSpecificProperty(tr("Reload time"), Properties::ReloadTime);
				break;
			default:
				break;
		}
	}
}

void ItemWidget::addSpecific(const QString &key, const QString &value)
{
	auto keyLabel = new QLabel(key);
	keyLabel->setFont(TitlesFont);

	auto valueLabel = new QLabel(value);
	valueLabel->setWordWrap(true);
	valueLabel->setFont(DetailsFont);

	specificsLayout_->addRow(keyLabel, valueLabel);
}

void ItemWidget::addSpecificProperty(const QString &key, const QString &property)
{
	QString value = prototype_->getProperty(property).toString();
	addSpecific(key, value);
}
