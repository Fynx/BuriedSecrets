/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "ItemsDisplay.hpp"

#include "DataManager/DataManager.hpp"
#include "UserInterface/ItemWidget.hpp"
#include "GameObjects/Item.hpp"
#include "Common/Strings.hpp"

const QSize ItemsDisplay::IconSize{24, 24};

ItemsDisplay::ItemsDisplay(DataManager *dataManager)
	: dataManager_(dataManager),
	  itemWidget_(nullptr),
	  itemsList_(nullptr),
	  inReset_(false)
{}

ItemWidget *ItemsDisplay::createItemWidget()
{
	//if was created before, then nullptr
	if (itemWidget_ != nullptr)
		return nullptr;

	itemWidget_ = new ItemWidget(dataManager_);
	return itemWidget_;
}

QListWidget *ItemsDisplay::createItemsList()
{
	//if was created before, then nullptr
	if (itemsList_ != nullptr)
		return nullptr;

	return itemsList_ = new QListWidget;
}

void ItemsDisplay::connectDisplays()
{
	QObject::connect(itemsList_, &QListWidget::currentItemChanged, this, &ItemsDisplay::onCurrentChanged);
}

void ItemsDisplay::setItemsList(const QSet<Item *> &items)
{
	QSet<const Prototype *> prototypes;
	for (auto &item : items)
		prototypes.insert(item->getPrototype());

	setItemsList(prototypes);
}

void ItemsDisplay::setItemsList(const QSet<const Prototype *> &prototypes)
{
	//FIXME itemsList->clear is hard to handle due to signals, hence this hack with inReset_
	inReset_ = true;
	itemsList_->clear();
	usedPrototypes_.clear();
	itemWidget_->clear();
	inReset_ = false;

	for (auto proto : prototypes) {
		QString itemName = proto->getProperty(Properties::Picture).toString();
		const Resource *res = dataManager_->getResource(itemName);
		QImage img;
		img.loadFromData(reinterpret_cast<const uchar *>(res->getData()), res->getDataLength());
		QIcon icon(QPixmap::fromImage(img).scaled(IconSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

		auto name = proto->getProperty(Properties::Name).toString();
		auto lwi = new QListWidgetItem(icon, name, itemsList_);
// 		lwi->setFlags(Qt::ItemFlag::ItemIsSelectable & Qt::ItemIsDragEnabled & Qt::ItemIsEnabled);
		lwi->setData(Qt::UserRole, QVariant({name}));
		lwi->setFont(QFont("Times", 18));
		usedPrototypes_.insert(name, proto);
	}

	if (!prototypes.isEmpty())
		itemsList_->setCurrentRow(0);

}

const Prototype *ItemsDisplay::currentPrototype() const
{
	return itemWidget_->prototype();
}

void ItemsDisplay::onCurrentChanged(QListWidgetItem *item)
{
	if (!inReset_)
		itemWidget_->setPrototype(usedPrototypes_[item->data(Qt::UserRole).toString()]);
}
