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

	const sf::Texture *getFrame(ImageMetaData key) const;
	int getNumDirections() const;

private:
	FrameSet frames;
	int numDirections;
};