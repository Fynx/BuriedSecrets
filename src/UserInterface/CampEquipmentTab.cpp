/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "CampEquipmentTab.hpp"

#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
#include "GameObjects/Unit.hpp"
#include "UserInterface/ItemWidget.hpp"

const QSize CampEquipmentTab::IconSize{24, 24};

CampEquipmentTab::CampEquipmentTab(Equipment *eq, DataManager *dataManager)
	: eq_(eq),
	  dataManager_(dataManager)
{
	initLayout();
	initConnections();
}

void CampEquipmentTab::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	itemWidget_ = new ItemWidget(dataManager_);
	layout->addWidget(itemWidget_, 1);

	layout->addWidget(createItemsList(), 1);
}

QWidget *CampEquipmentTab::createItemsList()
{
	itemsList_ = new QListWidget;

	for (auto item : eq_->getItems()) {
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

	return itemsList_;
}

void CampEquipmentTab::initConnections()
{
	connect(itemsList_, &QListWidget::itemActivated, this, &CampEquipmentTab::onItemActivated);
}

void CampEquipmentTab::onItemActivated(QListWidgetItem *item)
{
	Item *selectedItem = itemsUids_[item->data(Qt::UserRole).toInt()];
	itemWidget_->setItem(selectedItem);
}
