/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Entities/SpriteGraphicalEntity.hpp"


SpriteGraphicalEntity::SpriteGraphicalEntity(const Object *object, const QList<QPointF> &basePolygon,
						GraphicalEffectFactory *graphicalEffectFactory)
	: GraphicalEntity{object, basePolygon, graphicalEffectFactory}
{
	sprite.setScale(0.1, 0.1);
}


void SpriteGraphicalEntity::draw(sf::RenderTarget *renderTarget)
{
	renderTarget->draw(sprite);
}


void SpriteGraphicalEntity::setPosition(const QPointF &position)
{
	GraphicalEntity::setPosition(position);
	sprite.setPosition(position.x() - baseCentre.x(), position.y() - baseCentre.y());
}


QSizeF SpriteGraphicalEntity::getSizePx() const
{
	const auto size = sprite.getGlobalBounds();
	return QSizeF{size.width, size.height};
}


