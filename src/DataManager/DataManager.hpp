/* YoLoDevelopment, 2014
 * All rights reserved.
 *
 * Some parts based on FileIO.hpp by Bartosz Szreder (https://github.com/szreder/devUtil)
 */
#pragma once

#include "DataManager/Prototype.hpp"
#include "DataManager/Resource.hpp"
#include "DataManager/TextureSet.hpp"
#include "DebugManager/DebugManager.hpp"

#include <QtWidgets>

class DataManager {
public:
	DataManager();
	~DataManager();

	static const QString SavesExtension;
	static const QString localDataPath();
	static const QString savesPath();
	static const QString basePath();
	static const QString dataPath();
	QList <Prototype *> getAllPrototypes();
	const Prototype *getPrototype(const QString &name) const;
	const Resource *getResource(const QString &name) const;
	const TextureSet *getTextureSet(const QString &name) const;

	template <class T>
	void loadFromFile(const QString &path, T &s);
	template <class T>
	void saveToFile(const QString &path, const T &s);

	QJsonObject loadJsonFromFile(const QString &path);
	void saveJsonToFile(const QString &path, const QJsonObject &json);

	/**
	 * @brief Reads file as raw data and returns it as a QString.
	 *
	 * @param path The path to the file.
	 */
	QByteArray readRawData(const QString &path);

private:
	void loadPrototypes();
	void savePrototypes() const;
	void loadResources();

	/**
	 * @brief This method assert that all resources have been loaded properly and fails with an exception
	 * if not.
	 */
	void validateResources() const;

	QHash<QString, Prototype *> prototypes;
	QHash<QString, Resource *> resources;
	QHash<QString, TextureData *> texturesData;
	QHash<QString, TextureSet *> textureSets;
};

template <class T>
void DataManager::loadFromFile(const QString &path, T &s)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		warn(QString("DataManager: Failed to load file ") + path);
		assert(false);
		return;
	}

	QDataStream input(&file);
	input >> s;
}

template <class T>
void DataManager::saveToFile(const QString &path, const T &s)
{
	QSaveFile tmpFile(path);

	if (!tmpFile.open(QIODevice::WriteOnly)) {
		warn(QString("DataManager: Failed to save to ") + path);
		assert(false);
		return;
	}

	QDataStream output(&tmpFile);
	output << s;

	tmpFile.commit();
}
