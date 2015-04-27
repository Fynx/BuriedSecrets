/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Effects/UnitShadowEffect.hpp"

#include <cassert>

#include "Common/Enums.hpp"
#include "Graphics/Entities/TexturedGraphicalEntity.hpp"


UnitShadowEffect::UnitShadowEffect (const Viewport *viewport)
		: GraphicalEffect{viewport}
{}


void UnitShadowEffect::draw (const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget)
{
	const TexturedGraphicalEntity *texturedEntity = dynamic_cast<const TexturedGraphicalEntity *>(graphicalEntity);
	assert(texturedEntity != nullptr);
	const sf::Texture *texture = texturedEntity->getTexture();
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect{0, 0, static_cast<int>(texture->getSize().x),
					  static_cast<int>(texture->getSize().y)});
	sprite.setColor(sf::Color{255, 255, 255, 100});
	const QPointF &pos = texturedEntity->getPosition() - texturedEntity->getBaseCentre();
	sprite.setPosition(pos.x(), pos.y());
	renderTarget->draw(sprite);
}


int UnitShadowEffect::getOrderId() const
{
	return BS::Graphic::EffectOrder::UnitShadow;
}

