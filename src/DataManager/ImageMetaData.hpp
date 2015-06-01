/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QHash>
#include "Common/Enums.hpp"


/**
 * @brief MetaData for describing single images.
 *
 * Used as a key for a lot of maps.
 */
struct ImageMetaData {

	ImageMetaData() {}
	ImageMetaData(const BS::State &state, const BS::ItemType &weapon, const BS::Graphic::Direction &direction,
		      const int frame)
			: state{state}, weapon{weapon}, direction{direction}, frame{frame}
	{}

	BS::State state;
	BS::ItemType weapon;
	BS::Graphic::Direction direction;
	int frame;
};


inline bool operator==(const ImageMetaData& a, const ImageMetaData &b) {
	return a.state == b.state && a.weapon == b.weapon && a.direction == b.direction && a.frame == b.frame;
}


inline uint qHash(const ImageMetaData &imageMetaData) {
	QPair<int, QPair<quint8, QPair<quint8, quint8>>> p{imageMetaData.frame, {imageMetaData.state,
			{static_cast<quint8>(imageMetaData.weapon), imageMetaData.direction}}};
	return qHash(p);
}
