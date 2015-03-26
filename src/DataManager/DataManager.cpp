/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/DataManager.hpp"

#include <cassert>

#include "Common/Strings.hpp"
#include "DataManager/TextureSetData.hpp"
#include "DebugManager/DebugManager.hpp"

DataManager::DataManager()
{
	loadResources();
	loadPrototypes();
}

DataManager::~DataManager()
{
	qDeleteAll(prototypes);
	qDeleteAll(resources);
	qDeleteAll(textureSets);
	qDeleteAll(texturesData);
}

void DataManager::save() const
{
	savePrototypes();
}

QList<Prototype *> DataManager::getAllPrototypes()
{
	return prototypes.values();
}

QHash<QString, Prototype *> DataManager::getPrototypesMap()
{
	return prototypes;
}

const Prototype *DataManager::getPrototype(const QString &name) const
{
	if (!prototypes.contains(name)) {
		err(QString("Prototype ") + name + QString(" not found!"));
		return nullptr;
	}
	return prototypes[name];
}

const Resource *DataManager::getResource(const QString &name) const
{
	return resources[name];
}

const TextureSet *DataManager::getTextureSet(const QString &name) const
{
	if (!textureSets.contains(name)) {
		err("TextureSet " + name + " not found!");
		assert(false);
	}

	return textureSets[name];
}

void DataManager::addPrototype(const QString &name, Prototype *prototype)
{
	prototypes[name] = prototype;
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

void DataManager::saveJsonToFile(const QString &path, const QJsonObject &json) const
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
		warn(QString("DataManager: failed to load file ") + path);
	} else {
		result = file.readAll();
		dataInfo(QString("DataManager: loaded ") + path);
	}

	return result;
}

void DataManager::loadPrototypes()
{
	info("Loading prototypes...");
	QString path = "data/prototypes.json";
	QJsonObject json = loadJsonFromFile(path);

	int counter = 1;
	for (const QString &name : json.keys()) {
		Prototype *prototype = new Prototype;
		qDebug() << (QString("[") + QString::number(counter++) + "/"
			+ QString::number(json.keys().size()) + "]\t").toStdString().c_str() << name;
		prototype->setProperty(Properties::Name, name);
		prototype->loadFromJson(json[name].toObject());

		if (prototype->hasProperty(Data::TextureSet)) {
			prototype->setTextureSetData(new TextureSetData(getTextureSet(
				prototype->getProperty(Data::TextureSet).toString())));
		}

		//TODO I'm thinking about throwing all of this below into Prototype::loadFromJson

		/** Parsing for centre and base polygon (for those objects that have it). */
		if (prototype->hasProperty(Properties::BaseCentre)) {
			const QVariantList centre = prototype->getProperty(Properties::BaseCentre).toList();
			prototype->setBaseCentre(QPointF(centre[0].toFloat(), centre[1].toFloat()));
		} else if (prototype->hasProperty(Properties::BasePolygon)) {
			const QVariantList polygon = prototype->getProperty(Properties::BasePolygon).toList();
			QList<QPointF> basePolygon;
			QPointF baseCentre;

			for (const QVariant &p : polygon) {
				const QVariantList &point = p.toList();
				basePolygon.append(QPointF{point[0].toFloat(), point[1].toFloat()});
				baseCentre += basePolygon.back();
			}

			baseCentre /= basePolygon.length();
			prototype->setBasePolygon(basePolygon);
			prototype->setBaseCentre(baseCentre);
		}

		prototypes[name] = prototype;
	}

	info("done.");
}

void DataManager::savePrototypes() const
{
	info("Saving prototypes...");

	QString path = "data/prototypes2.json";

	QJsonObject json;

	int counter = 1;
	for (const QString &key : prototypes.keys()) {
		qDebug() << (QString("[") + QString::number(counter++) + "/"
			+ QString::number(prototypes.keys().size()) + "]\t").toStdString().c_str() << key;
		json[key] = prototypes[key]->saveToJson();
	}

	saveJsonToFile(path, json);

	info("done.");
}

void DataManager::loadResources()
{
	/** Look at README.md of DataManager for more info on the format. */
	const QString preffix = "data/";
	info("Loading resources...");
	QString resourcesListStr = readRawData(preffix + "ResourcesList.txt");
	QStringList resourcesList = resourcesListStr.split('\n', QString::SkipEmptyParts);

	QHash<QString, QList<QPair<QString, QString>>> textureSetsData;

	/** Load all the resources from the list. */
	int counter = 1;
	for (QString resourcePath: resourcesList) {
		if (!resourcePath.trimmed().isEmpty()) {
			info(QString("[") + QString::number(counter++) + "/" + QString::number(resourcesList.size()) +
				QString("]") + QString("\tloading ") + resourcePath);

			QJsonObject json = loadJsonFromFile(preffix + resourcePath);

			for (const QString &key : json.keys()) {
				const QJsonObject &obj = json[key].toObject();
				QString typeString = obj[Properties::Type].toString();
				if (typeString == Resources::Font
				           || typeString == Resources::Image) {
					/** Load the data from the file */
					QByteArray resourceData = readRawData(preffix + obj[Data::Data].toString());
					char *data = new char[resourceData.length()];
					memcpy(data, resourceData.data(), resourceData.length());

					Resource *resource = new Resource(data, resourceData.length());
					resources[key] = resource;
				} else if (typeString == Resources::TextureSet) {
					// Load the data from the file.
					QVariantMap texturesMap = obj[Data::Textures].toObject().toVariantMap();
					QList<QPair<QString, QString>> textureSet;
					for (auto it = texturesMap.constBegin(); it != texturesMap.constEnd(); ++it) {
						textureSet.append({it.key(), it.value().toString()});
					}
					textureSetsData[key] = textureSet;
				} else if (typeString == Resources::Texture) {
					// Create a new TextureData object.
					QByteArray textureData = readRawData(preffix + obj[Data::Path].toString());
					int rows = obj[Data::Rows].toInt();
					int columns = obj[Data::Columns].toInt();

					texturesData[key] = new TextureData(rows, columns, textureData);
				}
			}
		}
	}

	// Second pass - assemble TextureSets from TextureData
	for (auto it = textureSetsData.constBegin(); it != textureSetsData.constEnd(); ++it) {
		QList<QPair<QString, TextureData *>> textures;
		for (auto iter = it.value().constBegin(); iter != it.value().constEnd(); ++iter) {
			assert(texturesData.contains(iter->second));
			textures.append({iter->first, *texturesData.find(iter->second)});
		}

		textureSets[it.key()] = new TextureSet(textures);
	}

	info("done.");
}

void DataManager::validateResources() const
{}
