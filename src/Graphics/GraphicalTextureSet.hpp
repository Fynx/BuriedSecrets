/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "DataManager/ImageMetaData.hpp"
#include "Graphics/FrameSet.hpp"


/**
 * @brief This class represents a set of the graphical representations of textures.
 */
class GraphicalTextureSet {
public:
	/**
	 * @brief Takes ownership of the frameSet.
	 */
	GraphicalTextureSet(const FrameSet *frameSet);
	~GraphicalTextureSet();

	/**
	 * @brief Returns the texture for the given key.
	 *
	 * On failure, tries different configurations of default keys before failing.
	 */
	const sf::Texture *getFrame(ImageMetaData key = ImageMetaData{BS::State::Idle, BS::ItemType::Invalid,
								      BS::Graphic::Direction::Invalid, 0}) const;
	/**
	 * @brief Returns the number of directions for which there are textures in the set.
	 */
	int getNumDirections() const;

private:
	const FrameSet *frames;
	int numDirections;
};
