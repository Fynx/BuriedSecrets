/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Entities/TexturedGraphicalEntity.hpp"

#include <cassert>

#include "DebugManager/DebugManager.hpp"
#include "Graphics/GraphicalTextureSet.hpp"


TexturedGraphicalEntity::TexturedGraphicalEntity(const Object *object, const QList<QPointF> &basePolygon,
						 GraphicalEffectFactory *graphicalEffectFactory,
						 const GraphicalTextureSet* textureSet)
: SpriteGraphicalEntity{object, basePolygon, graphicalEffectFactory}, textureSet{textureSet}
{}


void TexturedGraphicalEntity::setDirection(const BS::Graphic::Direction &direction)
{
	this->direction = direction;
}


void TexturedGraphicalEntity::update(const float timeDelta)
{
	const sf::Texture *texture = textureSet->getFrame(getImageMetaData());
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect{0, 0, (int)texture->getSize().x, (int)texture->getSize().y});
}


const sf::Texture *TexturedGraphicalEntity::getTexture() const
{
	return sprite.getTexture();
}

