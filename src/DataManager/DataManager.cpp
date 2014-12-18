/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/DataManager.hpp"
#include "DebugManager/DebugManager.hpp"


DataManager::DataManager()
	: map(nullptr)
{
	loadResources();
	loadPrototypes();
}

DataManager::~DataManager()
{
	qDeleteAll(prototypes);
	qDeleteAll(resources);
	qDeleteAll(animationData);
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

const AnimationData *DataManager::getAnimationData(const QString &name) const
{
	return animationData[name];
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

	QString path = "data/prototypes.json";
	QFile prototypesFile(path);
	if (!prototypesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "DataManager: Failed to load file " << path;
		return;
	}

	QString text = prototypesFile.readAll();
	QJsonDocument jsonDoc = QJsonDocument::fromJson(text.toUtf8());
	if (jsonDoc.isNull()) {
		qDebug() << "DataManager: Error occurred while parsing prototypes file.";
		return;
	}
	QJsonObject json = jsonDoc.object();

	for (const QString &name : json.keys()) {
		Prototype *prototype = new Prototype;
		qDebug() << "\t" << name;
		for (const QString &key : json[name].toObject().keys()) {
			QJsonValue value = json[name].toObject()[key];
			prototype->setProperty(key, value.toVariant());
			qDebug() << "\t\t" << key << value.toVariant();
		}
		// FIXME hardcoded
		prototype->addAnimationData(BS::Idle, getAnimationData("SoszuIdle"));
		prototype->addAnimationData(BS::Run, getAnimationData("SoszuWalking"));

		prototypes[prototype->getProperty("name").toString()] = prototype;
	}

	qDebug() << "done";
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
			for (int i = 0; i + 2 < resourceInfo.length(); i += 3) {
				QString typeStr = resourceInfo.at(i + 1);

				if (typeStr == "Animation") {
					// Save bare string as data.
					AnimationData *animation = new AnimationData(
							resourceInfo.at(i), resourceInfo.at(i + 2));
					qDebug() << animation;
					animationData[resourceInfo.at(i)] = animation;
				} else if (typeStr == "Texture" || typeStr == "Font") {
					// Load the data from the file
					QByteArray resourceData = readRawData(prefix + resourceInfo.at(i + 2));
					char *data = new char[resourceData.length()];
					memcpy(data, resourceData.data(), resourceData.length());

					Resource *resource = new Resource(data, resourceData.length());
					resources[resourceInfo.at(i)] = resource;
				}

				qDebug() << "loaded " << resourceInfo.at(i);
			}

		}
	}
	qDebug() << "done.";
}

bool DataManager::loadMap(const QString &path)
{
	qDebug() << "\nCreating map...";
	delete map;
	map = nullptr;

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "DataManager: Failed to load file " << path;
		return false;
	}

	QString text = file.readAll();
	QJsonDocument jsonDoc = QJsonDocument::fromJson(text.toUtf8());
	if (jsonDoc.isNull()) {
		qDebug() << "DataManager: Error occurred while parsing map file.";
		return false;
	}
	QJsonObject json = jsonDoc.object();

	QString mapName = json["mapName"].toString();
	QString mapDesc = json["mapDesc"].toString();

	qDebug() << "mapName:" << mapName;
	qDebug() << "mapDesc:" << mapDesc;

	//TODO remove animators from the map,
	QVector<Map::Object> objects;
	for (const QString &key : json["objects"].toObject().keys()) {
		Map::Object object;
		object.name = key;
		object.properties = json["objects"].toObject()[key].toObject().toVariantMap();
		qDebug() << "\t" << key;
		for (const QString &kk : object.properties.keys())
			qDebug() << "\t\t" << kk << ":" << object.properties[kk];
		objects.append(object);
	}

	map = new Map(mapName, mapDesc, objects);

	return true;
}

void DataManager::validateResources() const
{
	for (const auto& anim: animationData) {
		for (const auto& frames: anim->getFramesDescription()) {
			for (const auto& str: frames) {
				assert(resources.contains(str));
				// TODO FIXME Assert that the type is a Texture.
			}
		}
	}
}
