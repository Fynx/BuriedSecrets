/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
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

QJsonObject DataManager::loadJsonFromFile(const QString &path)
{
	QJsonDocument jsonDoc = QJsonDocument::fromJson(readRawData(path));
	if (jsonDoc.isNull()) {
		err("DataManager: Error occurred while parsing .json file.");
		return QJsonObject();
	} else {
		return jsonDoc.object();
	}
}

void DataManager::saveJsonToFile(const QString &path, const QJsonObject &json)
{
	QSaveFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		err(QString("DataManager: Failed to save file ") + path);
		return;
	}

	QJsonDocument doc;
	doc.setObject(json);

	file.write(doc.toJson());

	file.commit();
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
	info("Loading prototypes...");
	warn("(we DON'T use Prototype::DataStream operators!)");

	QString path = "data/prototypes.json";

	QJsonObject json = loadJsonFromFile(path);

	int counter = 1;
	for (const QString &name : json.keys()) {
		Prototype *prototype = new Prototype;
		qDebug() << (QString("[") + QString::number(counter++) + "/"
			+ QString::number(json.keys().size()) + "]\t").toStdString().c_str() << name;
		prototype->setProperty(Properties::Name, name);
		for (const QString &key : json[name].toObject().keys()) {
			QJsonValue value = json[name].toObject()[key];
			prototype->setProperty(key, value.toVariant());
// 			qDebug() << "\t\t" << key << value.toVariant();
		}

		if (prototype->hasProperty(Properties::Animations)) {
			auto animations = prototype->getProperty(Properties::Animations).toMap();

			for (const QVariant &animation: animations) {
				const AnimationData *animData = getAnimationData(animation.toString());
				prototype->addAnimationData(animData->getState(), animData);
			}
		}

		prototypes[name] = prototype;
	}

	info("done");
}

void DataManager::savePrototypes() const
{
	qDebug() << "Save option NOT AVAILABLE!";
}

void DataManager::loadResources()
{
	/** Look at README.md of DataManager for more info on the format. */
	const QString preffix = "data/";
	info("Loading resources...");
	QString resourcesListStr = readRawData(preffix + "ResourcesList.txt");
	QStringList resourcesList = resourcesListStr.split('\n', QString::SkipEmptyParts);

	/** Load all the resources from the list. */
	int counter = 1;
	for (QString resourcePath: resourcesList) {
		if (!resourcePath.trimmed().isEmpty()) {
			info(QString("[") + QString::number(counter++) + "/" + QString::number(resourcesList.size()) +
				QString("]") + QString("\tloading ") + resourcePath);

			QJsonObject json = loadJsonFromFile(preffix + resourcePath);

			for (const QString &key : json.keys()) {
				const QJsonObject &obj = json[key].toObject();
				if (obj[Properties::Type].toString() == "animation") {
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

	info("done.");
}

bool DataManager::loadMap(const QString &path)
{
	qDebug() << "\nCreating map...";
	delete map;
	map = nullptr;

	QJsonObject json = loadJsonFromFile(path);

	QString mapName = json[Properties::MapName].toString();
	QString mapDesc = json[Properties::MapDesc].toString();

	qDebug() << "mapName:" << mapName;
	qDebug() << "mapDesc:" << mapDesc;

	map = new MapInfo(mapName, mapDesc);//, objects);

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
