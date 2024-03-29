/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "Mind/MapManager/Map.hpp"
#include "GameObjects/JournalEntry.hpp"

Map::Map(const QJsonObject &json)
	: json(json),
	  name(json[MapProperties::MapName].toString()),
	  desc(json[MapProperties::MapDesc].toString()),
	  title(json[MapProperties::MapTitle].toString()),
	  text(json[MapProperties::MapText].toString()),
	  size(json[MapProperties::MapWidth].toDouble(), json[MapProperties::MapHeight].toDouble())
{}

const QJsonObject &Map::getJson() const
{
	return json;
}

bool Map::isPointValid(const QPointF &point) const
{
	return point.x() >= 0.0f && point.y() >= 0.0f && point.x() <= size.width() && point.y() <= size.height();
}

const QString &Map::getName() const
{
	return name;
}

const QString &Map::getTitle() const
{
	return title;
}

const QString &Map::getText() const
{
	return text;
}

const QString &Map::getDesc() const
{
	return desc;
}

const QSizeF &Map::getSize() const
{
	return size;
}
