/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <SFML/Graphics.hpp>

#include "Graphics/SpriteGraphicalEntity.hpp"


/**
 * @brief This class represents a static graphical object that always displays the same image.
 *
 */
class StaticGraphicalEntity: public SpriteGraphicalEntity {
public:
	StaticGraphicalEntity(const Object* object, const sf::Texture *texture);

	void setDirection(const BS::Graphic::Direction &direction) override;
	void update(const float timeDelta) override;
};