/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "ItemWidget.hpp"

#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
#include "GameObjects/Item.hpp"

const QSize ItemWidget::PictureSize{256, 256};

ItemWidget::ItemWidget(DataManager *dataManager) : item_(nullptr), dataManager_(dataManager)
{
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
	layout->addLayout(createDetailsPart(), 1);
}

QLayout *ItemWidget::createMainPart()
{
	auto layout = new QVBoxLayout;

	pictureLabel_ = new QLabel;
	pictureLabel_->setAlignment(Qt::AlignCenter);
	layout->addWidget(pictureLabel_);

	nameLabel_ = new QLabel;
	nameLabel_->setFont(QFont("Times", 22));
	nameLabel_->setAlignment(Qt::AlignCenter);
	layout->addWidget(nameLabel_);

	return layout;
}

QLayout *ItemWidget::createDetailsPart()
{
	QFormLayout *layout = new QFormLayout;

	QFont font("Times", 16);

	weightLabel_ = new QLabel;
	weightLabel_->setFont(font);
	layout->addWidget(weightLabel_);

	auto details = new QLabel("<details goes here>");
	details->setFont(font);
	layout->addRow(details);

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
	weightLabel_->setText(tr("Weight: ") + QString::number(item_->getWeight()));
}
