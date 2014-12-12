/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/DataManager.hpp"

#include "DebugManager/DebugManager.hpp"

static const QHash<QString, bool> stringy {
	{"attack",       false},
	{"background",   false},
	{"capacity",     false},
	{"defense",      false},
	{"encumbrance",  false},
	{"engineering",  false},
	{"foodDemand",   false},
	{"healing",      false},
	{"hp",           false},
	{"perception",   false},
	{"position",     false},
	{"psychosis",    false},
	{"range",        false},
	{"regeneration", false},
	{"searchTime",   false},
	{"sightRange",   false},
	{"speed",        false},
	{"weight",       false},

	{"avatar",       true},
	{"itemType",     true},
	{"name",         true},
	{"type",         true},
};

DataManager::DataManager()
{
	loadPrototypes();
	loadResources();
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
	qDebug() << "Loading prototypes... (we DON'T use Prototype::DataStream operators!)";

	QStringList lines = QString(readRawData("data/prototypes.txt")).split("\n");

	Prototype *prototype = nullptr;
	QString key;
	QVariant value;

	for (const QString &line : lines) {
		if (!line.isEmpty() && line[0] != '#') {
			QStringList words = line.split(" ");
			if (words.size() == 1) {
				if (prototype != nullptr) {
					if (prototype->getProperty("name").toString().isEmpty()) {
						qDebug() << "\tPrototype without a name. Skipping.";
						delete prototype;
					} else {
						qDebug() << "\tLoaded" << prototype->getProperty("name").toString();
						prototypes[prototype->getProperty("name").toString()] = prototype;
					}
				}
				prototype = new Prototype();
				key = "type";
				value = words[0];
			} else {
				Q_ASSERT(prototype != nullptr);
				key = words[0];
				Q_ASSERT(stringy.contains(key));
				if (stringy[key])
					value = line.mid(words[0].size() + 1);
				else
					value = words[1].toInt();
			}
			prototype->setProperty(key, value);
		}
	}

	qDebug() << "done.\n";
}

void DataManager::savePrototypes() const
{
	qDebug() << "Save option NOT AVAILABLE!";
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
