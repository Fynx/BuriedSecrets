/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtCore>
#include "DataManager/Resource.hpp"

class Map {
public:
	struct Object {
		QString name;
		QStringList animators;
		QHash<QString, QString> properties;
	};

	Map(const QString &name, const QString &representationName, const QVector<Map::Object> &objects);

	QString getName() const;
	QString getRepresentationName() const;
// 	Resource *getRepresentation() const;
	const QVector<Map::Object> &getObjects() const;

private:
	const QString name;
	const QString representationName;
// 	Resource *representation;
	const QVector<Map::Object> objects;
};