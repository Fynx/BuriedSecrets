/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <SFML/Graphics.hpp>

#include "Graphics/GraphicalEntity.hpp"


/**
 * @brief This class represents a static graphical object that always displays the same image.
 *
 */
class StaticGraphicalEntity: public GraphicalEntity {
public:
	StaticGraphicalEntity(const Object* object, const sf::Texture *texture);

	sf::Drawable *getDrawable() override;
	void setPosition(const QPointF &position) override;
	void update(const float timeDelta) override;

private:
	sf::Sprite sprite;
};