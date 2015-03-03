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
	  itemsList_(nullptr)
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
	QObject::connect(itemsList_, &QListWidget::itemActivated, this, &ItemsDisplay::onItemActivated);
}

void ItemsDisplay::setItemsList(QSet<Item *> items)
{

	for (auto item : items) {
		QString itemName = item->getPrototype()->getProperty(Properties::Picture).toString();
		const Resource *res = dataManager_->getResource(itemName);
		QImage img;
		img.loadFromData(reinterpret_cast<const uchar *>(res->getData()), res->getDataLength());
		QIcon icon(QPixmap::fromImage(img).scaled(IconSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

		auto lwi = new QListWidgetItem(icon, item->getName(), itemsList_);
// 		lwi->setFlags(Qt::ItemFlag::ItemIsSelectable & Qt::ItemIsDragEnabled & Qt::ItemIsEnabled);
		lwi->setData(Qt::UserRole, QVariant(item->getUid()));
		lwi->setFont(QFont("Times", 18));
		itemsUids_.insert(item->getUid(), item);
	}

	if (!items.isEmpty())
		itemsList_->setCurrentRow(0);
}

void ItemsDisplay::onItemActivated(QListWidgetItem *item)
{
	Item *selectedItem = itemsUids_[item->data(Qt::UserRole).toInt()];
	itemWidget_->setItem(selectedItem);
}
