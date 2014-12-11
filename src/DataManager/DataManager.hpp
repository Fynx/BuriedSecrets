/* YoLoDevelopment, 2014
 * All rights reserved.
 *
 * Some parts based on FileIO.hpp by Bartosz Szreder (https://github.com/szreder/devUtil)
 */
#pragma once

#include "DataManager/AnimationData.hpp"
#include "DataManager/Map.hpp"
#include "DataManager/Prototype.hpp"
#include "DataManager/Resource.hpp"

#include <QtWidgets>


class DataManager {
public:
	DataManager();
	~DataManager();

	const Prototype *getPrototype(const QString &name) const;
	const Resource *getResource(const QString &name) const;
	const Map *getMap(const QString &path);
	const AnimationData *getAnimationData(const QString &name) const;

	template <class T>
	void loadFromFile(const QString &path, T &s);

	template <class T>
	void saveToFile(const QString &path, const T &s);

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
	bool loadMap(const QString &mapPath);

	/**
	 * @brief This method assert that all resources have been loaded properly and fails with an exception
	 * if not.
	 */
	void validateResources() const;

	QPair<QString, QVariant> readLine(const QString &line) const;

	QHash<QString, Prototype *> prototypes;
	QHash<QString, Resource *> resources;
	QHash <QString, AnimationData *> animationData;
	Map *map;
};


template <class T>
void DataManager::loadFromFile(const QString &path, T &s)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "DataManager: Failed to load file " << path;
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
		qDebug() << "DataManager: Failed to save to " << path;
		return;
	}

	QDataStream output(&tmpFile);
	output << s;

	tmpFile.commit();
}
