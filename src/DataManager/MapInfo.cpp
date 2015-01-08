/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "DataManager/MapInfo.hpp"

MapInfo::MapInfo(const QString &name, const QString &representationName)//, const QVector<MapInfo::Object> &objects)
	: name(name), representationName(representationName)
// 	, objects(objects)
{}

QString MapInfo::getName() const
{
	return name;
}

QString MapInfo::getRepresentationName() const
{
	return representationName;
}

// Resource *Map::getRepresentation() const
// {

// }

// const QVector<MapInfo::Object> &MapInfo::getObjects() const
// {
// 	return objects;
// }
