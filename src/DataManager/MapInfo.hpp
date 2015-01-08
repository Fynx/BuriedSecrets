/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtCore>
#include "DataManager/Resource.hpp"

class MapInfo {
public:
// 	struct Object {
// 		QString name;
// 		QVariantMap properties;
// 	};

	MapInfo(const QString &name, const QString &representationName);//, const QVector<MapInfo::Object> &objects);

	QString getName() const;
	QString getRepresentationName() const;
// 	Resource *getRepresentation() const;
// 	const QVector<MapInfo::Object> &getObjects() const;

private:
	const QString name;
	const QString representationName;
// 	Resource *representation;
// 	const QVector<MapInfo::Object> objects;
};