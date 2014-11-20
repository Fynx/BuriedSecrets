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
	qDebug() << "loadFromFile" << path;
	QByteArray array("aaa");
	QDataStream stream(array);
	stream >> s;
}

template <class T>
void DataManager::saveToFile(const QString &path, const T &s)
{
	qDebug() << "saveToFile" << path;
}