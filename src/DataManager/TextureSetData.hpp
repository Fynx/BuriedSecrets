/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QHash>

#include "DataManager/ImageMetaData.hpp"

class TextureSet;


/**
 * @brief This class represents logical data of a TextureSet (needed for whatever logical parts of the animations).
 */
class TextureSetData {
public:
	TextureSetData(const TextureSet* textureSet);

	int getFramesNumber(const BS::State state = BS::State::Idle,
			    const BS::ItemType weapon = BS::ItemType::Invalid) const;

private:
	QHash<ImageMetaData, int> framesNumber;	// This uses ImageMetaData as a key, but the frames in each IMD key
						// are set to an equal value (0).
};