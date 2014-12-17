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

static const QSet<QString> toMap {
	"animations"
};

DataManager::DataManager()
	: map(nullptr)
{
	loadPrototypes();
	loadResources();
}

DataManager::~DataManager()
{
	qDeleteAll(prototypes);
	qDeleteAll(resources);
	delete map;
}

const Prototype *DataManager::getPrototype(const QString &name) const
{
	return prototypes[name];
}

const Resource *DataManager::getResource(const QString &name) const
{
	return resources[name];
}

const Map *DataManager::getMap(const QString &path)
{
	loadMap(path);
	return map;
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
	for (const QString &line : lines) {
		QPair<QString, QVariant> pair = readLine(line);
		if (pair.first == "type") {
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
		}
		if (!pair.first.isEmpty()) {
			qDebug() << "\t\t" << pair.first << pair.second;
			prototype->setProperty(pair.first, pair.second);
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

bool DataManager::loadMap(const QString &mapPath)
{
	qDebug() << "\nCreating map...";
	delete map;
	map = nullptr;

	QString mapDsc = readRawData(mapPath);
	QStringList list = mapDsc.split('\n', QString::SkipEmptyParts);

	for (int i = 0; i < list.size(); ++i)
		if (list[i][0] == '#')
			list.removeAt(i--);

	if (list.size() < 2) {
		qDebug() << "failed!";
		return false;
	}

	QString name = list[0];
	QString representationName = list[1];

	qDebug() << "name:" << name;
	qDebug() << "representationName:" << representationName;

	QVector<Map::Object> objects;
	for (int i = 2; i < list.size();) {
		Map::Object object;
		object.name = list[i++];
		object.animators = list[i++].split(' ', QString::SkipEmptyParts);

		//TODO extremely strange bug, something wrong with properties here.
		QStringList properties = list[i].split(' ', QString::SkipEmptyParts);
		int size = properties.size();
		while (i < list.size() && size > 1) {
			object.properties[properties[0]] = properties[1];
			++i;
			if (i < list.size()) {
				QStringList properties = list[i].split(' ', QString::SkipEmptyParts);
				size = properties.size();
			}
		}

		qDebug() << "\t" << object.name;
		qDebug() << "\t\t" << object.animators;
		qDebug() << "\t\t" << object.properties;

		objects.append(object);
	}

	map = new Map(name, representationName, objects);

	qDebug() << "done.";
	return true;
}

QPair<QString, QVariant> DataManager::readLine(const QString &line) const
{
	if (!line.isEmpty() && line[0] != '#') {
		QString aLine = line;
		QStringList words = aLine.replace(",", " ").replace("[", " ").replace("]", " ").split(" ");
		if (words.size() == 1) {
			return {"type", words[0]};
		} else {
			if (stringy[words[0]]) {
				return {words[0], line.mid(words[0].size() + 1)};
			} else if (!toMap.contains(words[0])) {
				return {words[0], words[1].toInt()};
			} else {
				QHash<QString, QVariant> map;
				QString key;
				for (int i = 1; i < words.size(); ++i) {
					if (key.isEmpty()) {
						key = words[i];
					} else if (!words[i].isEmpty()) {
						map[key] = words[i];
						key = QString();
					}
				}
				return {words[0], map};
			}
		}
	}
	return {};
}
