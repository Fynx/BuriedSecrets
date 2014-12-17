/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "DataManager/Map.hpp"

Map::Map(const QString &name, const QString &representationName, const QVector<Map::Object> &objects)
	: name(name), representationName(representationName), objects(objects)
{}

QString Map::getName() const
{
	return name;
}

QString Map::getRepresentationName() const
{
	return representationName;
}

// Resource *Map::getRepresentation() const
// {

// }

const QVector<Map::Object> &Map::getObjects() const
{
	return objects;
}
