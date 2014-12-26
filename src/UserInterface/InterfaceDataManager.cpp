/*
 { *{ *license|lines_prepend:" * " }}
 */
#include "UserInterface/InterfaceDataManager.hpp"

#include "DataManager/DataManager.hpp"
#include "DataManager/Resource.hpp"

InterfaceDataManager::InterfaceDataManager(const DataManager *dataManager) : dataManager_(dataManager)
{}

InterfaceDataManager::~InterfaceDataManager()
{
	qDeleteAll(images_);
}

const QImage * InterfaceDataManager::getImage(const QString &name)
{
	QImage *result = nullptr;

	auto it = images_.find(name);
	if (it == images_.end()) {
		const Resource *image = dataManager_->getResource(name);
		const uchar *data = reinterpret_cast<const uchar *>(image->getData());
		int size = image->getDataLength();
		result = new QImage(QImage::fromData(data, size));
		images_[name] = result;
	} else
		result = *it;

	return result;
}
