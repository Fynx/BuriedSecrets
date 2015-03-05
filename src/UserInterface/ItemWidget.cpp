
/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "ItemWidget.hpp"

#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
#include "GameObjects/Item.hpp"
#include "UserInterface/Resources.hpp"

const QSize ItemWidget::PictureSize{200, 200};
const QSize ItemWidget::StarSize{30, 30};
const QMargins ItemWidget::DetailsContentMargin{0, 20, 0, 20};
const QFont ItemWidget::DetailsFont{"Times", 16};
const QFont ItemWidget::TitlesFont{"Arial", 16, QFont::Bold};


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

void ItemWidget::setPrototype(const Prototype* prototype)
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
	auto layout = new QFormLayout;

	layout->setContentsMargins(DetailsContentMargin);
	layout->setVerticalSpacing(VerticalSpacing);
	layout->setHorizontalSpacing(HorizontalSpacing);

	descriptionLabel_ = new QLabel;
	descriptionLabel_->setFont(DetailsFont);
	descriptionLabel_->setWordWrap(true);
	layout->addRow(descriptionLabel_);

	auto itemTypeTitle = new QLabel(tr("Type"));
	itemTypeTitle->setFont(TitlesFont);
	itemTypeLabel_ = new QLabel;
	itemTypeLabel_->setFont(DetailsFont);
	layout->addRow(itemTypeTitle, itemTypeLabel_);

	auto qualityTitle = new QLabel(tr("Quality"));
	qualityTitle->setFont(TitlesFont);
	auto starsLayout = new QHBoxLayout;
	for (int i = 0; i < Item::StarLimit; ++i) {
		stars_.append(new QLabel);
		starsLayout->addWidget(stars_.back());
	}
	starsLayout->addStretch();
	layout->addRow(qualityTitle, starsLayout);

	auto weightTitle = new QLabel(tr("Weight"));
	weightTitle->setFont(TitlesFont);
	weightLabel_ = new QLabel;
	weightLabel_->setFont(DetailsFont);
	layout->addRow(weightTitle, weightLabel_);

	componentsTitle_ = new QLabel(tr("Parts"));
	componentsTitle_->setFont(TitlesFont);
	componentsLabel_ = new QLabel;
	componentsLabel_->setFont(DetailsFont);
	layout->addRow(componentsTitle_, componentsLabel_);

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
	itemTypeLabel_->setText(prototype_->getProperty(Properties::ItemType).toString());

	auto components = prototype_->getProperty(Properties::Ingredients).toStringList();
	QString componentsTxt;
	for (QString name : components)
		componentsTxt += name + QString("\n");
	componentsLabel_->setVisible(components.count() > 0);
	componentsTitle_->setVisible(components.count() > 0);
	componentsLabel_->setText(componentsTxt);

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
