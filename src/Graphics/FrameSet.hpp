/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "DataManager/ImageMetaData.hpp"


class FrameSet : public QHash<ImageMetaData, sf::Texture *> {
public:
	~FrameSet();
};
