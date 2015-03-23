/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/GraphicalTextureSet.hpp"

#include "DebugManager/DebugManager.hpp"


GraphicalTextureSet::GraphicalTextureSet(const GraphicalTextureSet::FrameSet &frameSet)
		: frames{frameSet}
{
	QSet<BS::Graphic::Direction> directions;
	for (auto iter = frameSet.constBegin(); iter != frameSet.constEnd(); ++iter) {
		directions.insert(iter.key().direction);
	}
	numDirections = directions.size();
}


const sf::Texture *GraphicalTextureSet::getFrame(ImageMetaData key) const
{
	auto it = frames.find(key);
	if (it == frames.end()) {
		// Try without the weapon.
		warn("Couldn't get the frame for given meta data, trying without the weapon...");
		key.weapon = BS::ItemType::Invalid;

		it = frames.find(key);
		if (it == frames.end()) {
			// Try in idle state.
			warn("Couldn't get the frame even without the weapon, trying to fall back to Idle...");
			key.state = BS::State::Idle;

			it = frames.find(key);
			if (it == frames.end()) {
				err("Failed. Nothing to display.");
				assert(false);
			}
		}
	}

	return it.value();
}


int GraphicalTextureSet::getNumDirections() const
{
	return numDirections;
}
