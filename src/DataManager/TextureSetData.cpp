/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "DataManager/TextureSetData.hpp"

#include <cassert>

#include <QDebug>

#include "DataManager/TextureSet.hpp"
#include "DebugManager/DebugManager.hpp"


TextureSetData::TextureSetData(const TextureSet *textureSet)
{
	QHash<ImageMetaData, int> tempFramesNumber;
	const auto &frames = textureSet->getAllImages();
	for (const auto &elem: frames) {
		ImageMetaData key;
		key.state = elem.first.state;
		key.weapon = elem.first.weapon;
		key.frame = 0;
		key.direction = elem.first.direction;
		tempFramesNumber[key]++;
	}

	for (auto iter = tempFramesNumber.begin(); iter != tempFramesNumber.end(); ++iter) {
		ImageMetaData key(iter.key());
		key.direction = BS::Graphic::Direction::Invalid;
		framesNumber[key] = iter.value();
	}
}


int TextureSetData::getFramesNumber(const BS::State state, const BS::ItemType weapon) const
{
	auto key = ImageMetaData(state, weapon, BS::Graphic::Direction::Invalid, 0);
	// FIXME this copies the logic from GraphicalTextureSet.
	// It's a fallback logic, needed mostly for testing and debug and should *NEVER* be used in the final
	// environment. However, it would be nice if those two pieces of code could somehow be merged.
	auto it = framesNumber.find(key);
	if (it == framesNumber.end()) {
		// Try without the weapon.
// 		warn("Couldn't get the frame number for given meta data, trying without the weapon...");
		key.weapon = BS::ItemType::Invalid;

		it = framesNumber.find(key);
		if (it == framesNumber.end()) {
			// Try in idle state.
// 			warn("Couldn't get the frame number even without the weapon, trying to fall back to Idle...");
			key.state = BS::State::Idle;

			it = framesNumber.find(key);
			if (it == framesNumber.end()) {
				err("Failed.");
				assert(false);
			}
		}
	}

	return it.value();
}
