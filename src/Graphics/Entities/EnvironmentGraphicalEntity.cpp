/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Entities/EnvironmentGraphicalEntity.hpp"


EnvironmentGraphicalEntity::EnvironmentGraphicalEntity(const Environment *environmentObject,
						       const QList<QPointF> &basePolygon,
						       GraphicalEffectFactory *graphicalEffectFactory,
						       const GraphicalTextureSet *textureSet)
		: TexturedGraphicalEntity{environmentObject, basePolygon, graphicalEffectFactory, textureSet}
		, environmentObject{environmentObject}
{}


void EnvironmentGraphicalEntity::update(const float timeDelta)
{
	if (!environmentObject->isTransparent()) {
		TexturedGraphicalEntity::update(timeDelta);
	}
}


ImageMetaData EnvironmentGraphicalEntity::getImageMetaData() const
{
	ImageMetaData metaData;

	metaData.direction = BS::Graphic::Direction::Invalid;
	metaData.frame = environmentObject->getFrame();
	metaData.weapon = BS::ItemType::Invalid;
	metaData.state = BS::State::Idle;

	return metaData;
}

