/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "DataManager/ImageMetaData.hpp"
#include "Graphics/FrameSet.hpp"


class GraphicalTextureSet {
public:
	GraphicalTextureSet(const FrameSet *frameSet);
	~GraphicalTextureSet();

	const sf::Texture *getFrame(ImageMetaData key = ImageMetaData{BS::State::Idle, BS::ItemType::Invalid,
								      BS::Graphic::Direction::Invalid, 0}) const;
	int getNumDirections() const;

private:
	const FrameSet *frames;
	int numDirections;
};
