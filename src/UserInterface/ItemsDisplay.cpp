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

	itemsList_ = new QListWidget;
	itemsList_->setSelectionMode(QAbstractItemView::SingleSelection);
	itemsList_->setDragEnabled(true);
	itemsList_->viewport()->setAcceptDrops(true);
	itemsList_->setDropIndicatorShown(true);
	itemsList_->setDragDropMode(QAbstractItemView::InternalMove);
	return itemsList_;
}

void ItemsDisplay::connectDisplays()
{
	QObject::connect(itemsList_, &QListWidget::currentItemChanged, this, &ItemsDisplay::onCurrentChanged);
}

void ItemsDisplay::setItemsList(const QList<Item *> &items)
{
	QList<QPair<const Prototype *, QVariant>> dataPairs;
	for (auto item : items)
		dataPairs.append({item->getPrototype(), QVariant(item->getUid())});

	setItemsList(dataPairs);
}

void ItemsDisplay::setItemsList(const QList<const Prototype *> &prototypes)
{
	QList<QPair<const Prototype *, QVariant>> dataPairs;
	for (int i = 0; i < prototypes.count(); ++ i)
		dataPairs.append({prototypes[i], QVariant(i)});

	setItemsList(dataPairs);
}

void ItemsDisplay::setItemsList(const QList<QPair<const Prototype *, QVariant>> &dataPairs)
{
	//FIXME itemsList->clear is hard to handle due to signals, hence this hack with inReset_
	inReset_ = true;
	itemsList_->clear();
	usedPrototypes_.clear();
	itemWidget_->clear();
	inReset_ = false;

	for (auto &pair : dataPairs) {
		auto proto = pair.first;
		QString itemName = proto->getProperty(Properties::Picture).toString();
		const Resource *res = dataManager_->getResource(itemName);
		QImage img;
		img.loadFromData(reinterpret_cast<const uchar *>(res->getData()), res->getDataLength());
		QIcon icon(QPixmap::fromImage(img).scaled(IconSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

		auto name = proto->getProperty(Properties::Name).toString();
		auto lwi = new QListWidgetItem(icon, name, itemsList_);
		lwi->setFlags(Qt::ItemFlag::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
		lwi->setData(Qt::UserRole, pair.second);
		lwi->setFont(QFont("Times", 18));
		usedPrototypes_.insert(pair.second, proto);
	}

	if (!dataPairs.isEmpty())
		itemsList_->setCurrentRow(0);
}

const Prototype *ItemsDisplay::currentPrototype() const
{
	return itemWidget_->prototype();
}

void ItemsDisplay::onCurrentChanged(QListWidgetItem *item)
{
	if (!inReset_) {
		itemWidget_->setPrototype(usedPrototypes_[item->data(Qt::UserRole)]);
		emit itemChanged(item->data(Qt::UserRole));
	}
}
