/* YoLoDevelopment, 2014
 * All rights reserved.
 *
 * Some parts based on FileIO.hpp by Bartosz Szreder (https://github.com/szreder/devUtil)
 */
#pragma once

#include "DataManager/Prototype.hpp"

#include <QtWidgets>


class DataManager {
public:
	DataManager();
	~DataManager();

	const Prototype *getPrototype(const QString &name) const;

	template <class T>
	void loadFromFile(const QString &path, T &s);

	template <class T>
	void saveToFile(const QString &path, const T &s);

private:
	void loadPrototypes();

	QHash <QString, Prototype *> prototypes;
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
	qDebug() << "DataManager: Loaded " << path;
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
}