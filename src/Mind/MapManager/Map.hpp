/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "DataManager/MapInfo.hpp"


/**
 * @brief Logical representation of the map.
 *
 */
class Map {
public:
// 	Map(const MapInfo *mapInfo);
	Map(const QJsonObject &json);

	const QJsonObject &getJson() const;
// 	const MapInfo *getMapInfo() const;
	/**
	 * @brief True if point (x, y) can be stepped on. False otherwise.
	 */
	bool canStepAt(const float x, const float y) const;

	QString getName() const;
	QString getDesc() const;

private:
// 	const MapInfo *mapInfo;
	//TODO extract data into fields or something
	QJsonObject json;
};