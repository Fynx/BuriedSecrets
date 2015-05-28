/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "DataManager/ImageMetaData.hpp"


/**
 * @brief This is just a standard QHash with added destructor for managing textures' deallocation.
 *
 */
class FrameSet: public QHash<ImageMetaData, sf::Texture *> {
public:
	~FrameSet();
};
