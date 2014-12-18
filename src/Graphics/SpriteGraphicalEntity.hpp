/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <SFML/Graphics.hpp>

#include "Graphics/GraphicalEntity.hpp"


class SpriteGraphicalEntity: public GraphicalEntity {
public:
	SpriteGraphicalEntity(const Object *object);

	sf::Drawable *getDrawable() override;
	void setPosition(const QPointF &position) override;
	virtual void setDirection(const BS::Graphic::Direction &direction) = 0;

protected:
	sf::Sprite sprite;
};