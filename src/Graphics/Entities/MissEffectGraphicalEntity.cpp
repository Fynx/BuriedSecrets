/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Entities/MissEffectGraphicalEntity.hpp"

#include <cassert>

#include "Graphics/GraphicalTextureSet.hpp"
#include "Mind/PointToPointEffectData.hpp"
#include "UserInterface/Viewport/Viewport.hpp"


MissGraphicalEntity::MissGraphicalEntity(const Viewport *viewport, const GraphicalTextureSet *missTextureSet)
		: EffectGraphicalEntity{viewport}, missTextureSet{missTextureSet}
{
	sprite.setTexture(*(missTextureSet->getFrame()));
}


void MissGraphicalEntity::draw(sf::RenderTarget *renderTarget)
{
	renderTarget->draw(sprite);
}


void MissGraphicalEntity::update (const float timeDelta)
{
	// TODO Animation here
}


void MissGraphicalEntity::updateData (const EffectData *effectData)
{
	const PointToPointEffectData *ptpData = dynamic_cast<const PointToPointEffectData *>(effectData);
	assert(ptpData != nullptr);

	QPointF pos = viewport->fromMetresToPixels(ptpData->getDestination());
	sprite.setPosition(pos.x() - sprite.getTexture()->getSize().x / 2.0f,
			   pos.y() - sprite.getTexture()->getSize().y / 2.0f);
}
