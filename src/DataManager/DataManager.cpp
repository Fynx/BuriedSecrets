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
	if (!prototypes.contains(name))
		qDebug() << "Prototype" << name << "not found!";
	Q_ASSERT(prototypes.contains(name));
	return prototypes[name];
}

const Resource *DataManager::getResource(const QString &name) const
{
	return resources[name];
}

const MapInfo *DataManager::getMap(const QString &path)
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

QJsonObject DataManager::readJson(const QString &path)
{
	QJsonDocument jsonDoc = QJsonDocument::fromJson(readRawData(path));
	if (jsonDoc.isNull()) {
		qDebug() << "DataManager: Error occurred while parsing .json file.";
		return QJsonObject();
	} else {
		return jsonDoc.object();
	}
}

void DataManager::loadPrototypes()
{
	qDebug() << "Loading prototypes... (we DON'T use Prototype::DataStream operators!)";

	QString path = "data/prototypes.json";

	QJsonObject json = readJson(path);

	for (const QString &name : json.keys()) {
		Prototype *prototype = new Prototype;
		qDebug() << "\t" << name;
		for (const QString &key : json[name].toObject().keys()) {
			QJsonValue value = json[name].toObject()[key];
			prototype->setProperty(key, value.toVariant());
			qDebug() << "\t\t" << key << value.toVariant();
		}

		if (prototype->hasProperty("animations")) {
			auto animations = prototype->getProperty("animations").toMap();

			for (const auto& animation: animations) {
				const AnimationData *animData = getAnimationData(animation.toString());
				prototype->addAnimationData(animData->getState(), animData);
			}
		}

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
	/** Look at README.md of DataManager for more info on the format. */
	const QString preffix = "data/";
	qDebug() << "Loading resources...";
	QString resourcesListStr = readRawData(preffix + "ResourcesList.txt");
	QStringList resourcesList = resourcesListStr.split('\n');

	/** Load all the resources from the list. */
	for (QString resourcePath: resourcesList) {
		if (!resourcePath.trimmed().isEmpty()) {
			qDebug() << "\tloading" << resourcePath;
			QJsonObject json = readJson(preffix + resourcePath);

			for (const QString &key : json.keys()) {
				const QJsonObject &obj = json[key].toObject();
				if (obj["type"].toString() == "animation") {
					AnimationData *animation = new AnimationData(
						key,
						BS::getStateFromString(obj["state"].toString()),
						obj["framesNumber"].toInt(),
						obj["frames"].toArray().toVariantList()
    					);
					qDebug() << animation;
					animationData[key] = animation;
				} else if (obj["type"].toString() == "texture" || obj["type"].toString() == "font") {
					/** Load the data from the file */
					QByteArray resourceData = readRawData(preffix + obj["data"].toString());
					char *data = new char[resourceData.length()];
					memcpy(data, resourceData.data(), resourceData.length());
//
					Resource *resource = new Resource(data, resourceData.length());
					resources[key] = resource;
				}
			}
			qDebug() << "loaded" << resourcePath;
		}
	}

	qDebug() << "done.";
}

bool DataManager::loadMap(const QString &path)
{
	qDebug() << "\nCreating map...";
	delete map;
	map = nullptr;

	QJsonObject json = readJson(path);

	QString mapName = json["mapName"].toString();
	QString mapDesc = json["mapDesc"].toString();

	qDebug() << "mapName:" << mapName;
	qDebug() << "mapDesc:" << mapDesc;

	//TODO remove animators from the map,
	QVector<MapInfo::Object> objects;
	for (const QString &key : json["objects"].toObject().keys()) {
		MapInfo::Object object;
		object.name = key;
		object.properties = json["objects"].toObject()[key].toObject().toVariantMap();
		qDebug() << "\t" << key;
		for (const QString &kk : object.properties.keys())
			qDebug() << "\t\t" << kk << ":" << object.properties[kk];
		objects.append(object);
	}

	map = new MapInfo(mapName, mapDesc, objects);

	return true;
}

void DataManager::validateResources() const
{
	for (const auto &anim: animationData) {
		for (const auto &frames: anim->getFramesDescription()) {
			for (const auto &str: frames) {
				assert(resources.contains(str));
				// TODO FIXME Assert that the type is a Texture.
			}
		}
	}
}
