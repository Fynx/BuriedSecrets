/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/MoveCommandEffectGraphicalEntity.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/PointEffectData.hpp"


MoveCommandEffectGraphicalEntity::MoveCommandEffectGraphicalEntity(const Viewport *viewport,
								   const sf::Texture *texture)
		: EffectGraphicalEntity{viewport}
{
	sprite.setTexture(*texture);
// 	sprite.setScale(0.8, 0.8);	// TODO temporary.
}


void MoveCommandEffectGraphicalEntity::draw(sf::RenderTarget *renderTarget)
{
	renderTarget->draw(sprite);
}


void MoveCommandEffectGraphicalEntity::update(const float timeDelta)
{}


void MoveCommandEffectGraphicalEntity::updateData(const EffectData *effectData)
{
	const PointEffectData *pdata = dynamic_cast<const PointEffectData *>(effectData);
	if (pdata == nullptr) {
		err("Move Command effect entity: Cannot cast to PointEffectData");
		Q_ASSERT(false);
	}

	QPointF pos = viewport->fromMetresToPixels(pdata->getPoint());
	// FIXME this assumes the texture is symmetric.
	sprite.setPosition(pos.x() - sprite.getGlobalBounds().width / 2.0f, pos.y() - sprite.getGlobalBounds().height);
}


