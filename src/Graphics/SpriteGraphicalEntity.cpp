/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/SpriteGraphicalEntity.hpp"


SpriteGraphicalEntity::SpriteGraphicalEntity(const Object *object)
	: GraphicalEntity(object)
{
	sprite.setScale(0.05, 0.05);
}


sf::Drawable *SpriteGraphicalEntity::getDrawable()
{
	return &sprite;
}


void SpriteGraphicalEntity::setPosition(const QPointF &position)
{
	sprite.setPosition(position.x(), position.y());
}


