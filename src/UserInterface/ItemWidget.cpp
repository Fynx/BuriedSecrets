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


ItemWidget::ItemWidget(DataManager *dataManager) : item_(nullptr), dataManager_(dataManager)
{
	setAutoFillBackground(true);
	initLayout();
}

const Item *ItemWidget::item() const
{
	return item_;
}

void ItemWidget::setItem(const Item *item)
{
	item_ = item;

	fillWidget();
}

void ItemWidget::initLayout()
{
	auto layout = new QHBoxLayout;
	setLayout(layout);
	layout->addLayout(createMainPart(), 1);
	layout->addLayout(createDetailsPart(), 2);
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
	QString pictureName = item_->getPrototype()->getProperty(Properties::Picture).toString();
	const Resource *res = dataManager_->getResource(pictureName);
	QImage img;
	img.loadFromData(reinterpret_cast<const uchar *>(res->getData()), res->getDataLength());
	QPixmap pixmap(QPixmap::fromImage(img).scaled(PictureSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	pictureLabel_->setPixmap(pixmap);

	nameLabel_->setText(item_->getName());

	// Details
	descriptionLabel_->setText(item_->getPrototype()->getProperty(Properties::Description).toString());

	weightLabel_->setNum(item_->getWeight());
	fillQuality(item_->getPrototype()->getProperty(Properties::Quality).toInt());
	itemTypeLabel_->setText(BS::changeItemTypeToString(item_->getItemType()));

	auto components = item_->getPrototype()->getProperty(Properties::Ingredients).toStringList();
	QString componentsTxt;
	for (QString name : components)
		componentsTxt += QString("- ") + name + QString("\n");
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
