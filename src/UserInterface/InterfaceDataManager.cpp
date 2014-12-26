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
		const Resource *resource = dataManager_->getResource(name);
		const uchar *data = reinterpret_cast<const uchar *>(resource->getData());
		int size = resource->getDataLength();
		result = new QImage(QImage::fromData(data, size));
		images_[name] = result;
	} else
		result = *it;

	return result;
}

const QPixmap * InterfaceDataManager::getPixmap(const QString &name)
{
	QPixmap *result = nullptr;

	auto it = pixmaps_.find(name);
	if (it == pixmaps_.end()) {
		const QImage *image = getImage(name);
		result = new QPixmap(QPixmap::fromImage(*image));
		pixmaps_[name] = result;
	} else
		result = *it;

	return result;
}

const QIcon * InterfaceDataManager::getIcon(const QString &name)
{
	QIcon *result = nullptr;

	auto it = icons_.find(name);
	if (it == icons_.end()) {
		const QImage *image = getImage(name);

		result = new QIcon(QPixmap(QPixmap::fromImage(*image)));
		icons_[name] = result;
	} else
		result = *it;

	return result;
}
