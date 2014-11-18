#pragma once

#include <QtWidgets>

class DataManager {
public:
	DataManager();

	template <class T>
	void loadFromFile(const QString &path, T &s);

	template <class T>
	void saveToFile(const QString &path, const T &s);
};


template <class T>
void DataManager::loadFromFile(const QString &path, T &s)
{
	qDebug() << "loadFromFile" << path;
}

template <class T>
void DataManager::saveToFile(const QString &path, const T &s)
{
	qDebug() << "saveToFile" << path;
}