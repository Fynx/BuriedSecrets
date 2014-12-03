/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/DataManager.hpp"


DataManager::DataManager()
{
	loadPrototypes();
	loadResources();
}


DataManager::~DataManager()
{
	qDeleteAll(prototypes);
}


const Prototype *DataManager::getPrototype(const QString &name) const
{
	return prototypes[name];
}


const Resource* DataManager::getResource(const QString& name) const
{
	return resources[name];
}


QString DataManager::readRawData(const QString& path)
{
	QString result;
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "DataManager: Failed to load file " << path;
	} else {
		QTextStream input(&file);
		result = input.readAll();
		qDebug() << "DataManager: Loaded " << path;
	}

	return result;
}


void DataManager::loadPrototypes()
{
	Prototype *p = new Prototype();

	loadFromFile("prototypeFile", *p);

	p->setProperty("name", "ItsATrap");

	prototypes["ItsATrap"] = p;
}


void DataManager::loadResources()
{
	// Look at README.md of DataManager for more info on the format.
	const QString prefix = "data/";
	qDebug() << "Loading resources...";
	QString resourcesListStr = readRawData(prefix + "ResourcesList.txt");
	QStringList resourcesList = resourcesListStr.split('\n');

	// Load all the resources from the list.
	for (QString resourcePath: resourcesList) {
		if (!resourcePath.trimmed().isEmpty()) {
			qDebug() << "Loading " << resourcePath;
			QString resourceStr = readRawData(prefix + resourcePath);
			QStringList resourceInfo = resourceStr.split('\n');

			QString resourceData = readRawData(prefix + resourceInfo.at(2)); // load the data from the file

			ResourceType type = (resourceInfo.at(1) == "Texture")
					? ResourceType::Texture : ResourceType::Font;
			char *data = new char[resourceData.length()];
			strcpy(data, resourceData.toStdString().c_str());

			Resource *resource = new Resource(type, data, resourceData.length());
			resources[resourceInfo.at(0)] = resource;
		}
	}
	qDebug() << "Successfully loaded resources.";
}
