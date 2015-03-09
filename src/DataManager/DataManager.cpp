/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
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
	qDeleteAll(animationData);
}

QList <Prototype *> DataManager::getAllPrototypes()
{
	return prototypes.values();
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
		for (const QString &key : json[name].toObject().keys()) {
			QJsonValue value = json[name].toObject()[key];
			prototype->setProperty(key, value.toVariant());
// 			qDebug() << "\t\t" << key << value.toVariant();
		}

		if (prototype->hasProperty(Data::Animations)) {
			auto animations = prototype->getProperty(Data::Animations).toMap();

			for (const QString &key : animations.keys()) {
				const AnimationData *animData = getAnimationData(animations[key].toString());
				prototype->addAnimationData(BS::changeStringToState(key), animData);
			}
		}

		// Parsing for centre and base polygon (for those objects that have it).
		if (prototype->hasProperty(Properties::BaseCentre)) {
			const QVariantList centre = prototype->getProperty(Properties::BaseCentre).toList();
			prototype->setBaseCentre(QPointF(centre[0].toFloat(), centre[1].toFloat()));
		} else if (prototype->hasProperty(Properties::BasePolygon)) {
			const QVariantList polygon = prototype->getProperty(Properties::BasePolygon).toList();
			QList<QPointF> basePolygon;
			QPointF baseCentre;

			for (const QVariant &p: polygon) {
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
	err("Save option NOT AVAILABLE!");
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
				QString typeString = obj[Properties::Type].toString();
				if (typeString == Resources::Animation) {
					AnimationData *animation = new AnimationData(
						key,
						BS::changeStringToState(obj[TempData::State].toString()),
						obj[AnimationProperties::FramesNumber].toInt(),
						obj[AnimationProperties::Frames].toArray().toVariantList()
					);
					qDebug() << key << obj[TempData::State].toString();
					animationData[key] = animation;
				} else if (typeString == Resources::Texture || typeString == Resources::Font
				           || typeString == Resources::Image) {
					/** Load the data from the file */
					QByteArray resourceData = readRawData(preffix + obj[Data::Data].toString());
					char *data = new char[resourceData.length()];
					memcpy(data, resourceData.data(), resourceData.length());

					Resource *resource = new Resource(data, resourceData.length());
					resources[key] = resource;
				}
			}
		}
	}

	info("done.");
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
