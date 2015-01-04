/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/SpriteGraphicalEntity.hpp"


SpriteGraphicalEntity::SpriteGraphicalEntity(const Object *object, const QList<QPointF> &basePolygon)
	: GraphicalEntity{object, basePolygon}
{
	sprite.setScale(0.05, 0.05);
}


sf::Drawable *SpriteGraphicalEntity::getDrawable()
{
	return &sprite;
}


void SpriteGraphicalEntity::setPosition(const QPointF &position)
{
	sprite.setPosition(position.x() - baseCentre.x(), position.y() - baseCentre.y());
}


