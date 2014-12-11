/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/DataManager.hpp"

DataManager::DataManager()
{
	loadPrototypes();
	loadResources();
	//TODO remove this. It's just for hardcoding things.
	savePrototypes();
}

DataManager::~DataManager()
{
	qDeleteAll(prototypes);
	qDeleteAll(resources);
}

const Prototype *DataManager::getPrototype(const QString &name) const
{
	return prototypes[name];
}

const Resource *DataManager::getResource(const QString &name) const
{
	return resources[name];
}

QByteArray DataManager::readRawData(const QString &path)
{
	QByteArray result;
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "DataManager: Failed to load file " << path;
	} else {
		result = file.readAll();
		qDebug() << "DataManager: Loaded " << path;
	}

	return result;
}

void DataManager::loadPrototypes()
{
	//TODO this shouldn't be here. Create an object and use loadFromFile
	QString path = "data/prototypes.bin";
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "DataManager: Failed to load file " << path;
		return;
	}
	QDataStream in(&file);
	//

	qint32 prototypesNumber;

	in >> prototypesNumber;

	qDebug() << "Loading" << prototypesNumber << "prototypes...";

	for (int i = 0; i < prototypesNumber; ++i) {
		QString name;
		in >> name;
		qDebug() << "\tloading" << name;

		Prototype *p = prototypes.contains(name)
			? prototypes[name]
			: new Prototype();
		in >> *p;
		prototypes[name] = p;
	}

	qDebug() << "done.\n";
}

void DataManager::savePrototypes() const
{
	//TODO this shouldn't be here. Create an object and use saveFromFile
	QString path = "data/prototypes.bin";
	QSaveFile tmpFile(path);

	if (!tmpFile.open(QIODevice::WriteOnly)) {
		qDebug() << "DataManager: Failed to save to " << path;
		return;
	}

	QDataStream out(&tmpFile);

	qDebug() << "Saving prototypes...";

	//FIXME it's fixed prototypes now
	//TODO tum tum tum

	qint32 prototypesNumber = 3;

	out << prototypesNumber;

	Prototype building;
	building.setProperty("capacity", 5);
	building.setProperty("inhabitants", 0);
	building.setProperty("range", 10.0);
	building.setProperty("attack", 0);
	building.setProperty("defense", 0);
	building.setProperty("searchTime", 5);

	out << QString("building") << building;

	Prototype fortification;
	fortification.setProperty("hitPoints", 10);
	fortification.setProperty("attack", 0);
	fortification.setProperty("defense", 0);

	out << QString("fortification") << fortification;

	Prototype character;
	character.setProperty("name", "MuahahahaCharacter");
	character.setProperty("background", "12 years old commando raised by his 89 years old commando grandma.");
	character.setProperty("position", "engineer");
	character.setProperty("avatar", "sweetseal");
	character.setProperty("age", 10023);

	character.setProperty("attack", 10);
	character.setProperty("engineering", 10);
	character.setProperty("healing", 10);
	character.setProperty("perception", 10);
	character.setProperty("defense", 10);

	character.setProperty("hp", 100);
	character.setProperty("psyche", 100);
	character.setProperty("capacity", 5);
	character.setProperty("hunger", 1.5);
	character.setProperty("sightRange", 30);
	character.setProperty("speed", 2);
	character.setProperty("regeneration", 1);

	out << QString("character") << character;

	if (tmpFile.commit())
		qDebug() << "done.";
	else
		qDebug() << "failed!";
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
			qDebug() << "\tloading" << resourcePath;
			QString resourceStr = readRawData(prefix + resourcePath);
			QStringList resourceInfo = resourceStr.split('\n');

			// load the data from the file
			QByteArray resourceData = readRawData(prefix + resourceInfo.at(2));

			ResourceType type = (resourceInfo.at(1) == "Texture")
				? ResourceType::Texture
				: ResourceType::Font;
			char *data = new char[resourceData.length()];
			memcpy(data, resourceData.data(), resourceData.length());

			Resource *resource = new Resource(type, data, resourceData.length());
			resources[resourceInfo.at(0)] = resource;
		}
	}
	qDebug() << "done.";
}
