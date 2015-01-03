/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/MapManager/Map.hpp"


Map::Map(const MapInfo *mapInfo)
	: mapInfo{mapInfo}
{}


const MapInfo *Map::getMapInfo() const
{
	return mapInfo;
}

