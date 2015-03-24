/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "DataManager/ImageMetaData.hpp"


class GraphicalTextureSet {
public:
	typedef QHash<ImageMetaData, sf::Texture *> FrameSet;
	GraphicalTextureSet(const FrameSet &frameSet);

	const sf::Texture *getFrame(ImageMetaData key = ImageMetaData{BS::State::Idle, BS::ItemType::Invalid,
								      BS::Graphic::Direction::Invalid, 0}) const;
	int getNumDirections() const;

private:
	FrameSet frames;
	int numDirections;
};