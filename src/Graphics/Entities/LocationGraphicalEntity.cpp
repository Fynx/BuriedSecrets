/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Entities/LocationGraphicalEntity.hpp"

#include "GameObjects/Location.hpp"
#include "Graphics/GraphicalTextureSet.hpp"


LocationGraphicalEntity::LocationGraphicalEntity(const Location *location, const QList<QPointF> &basePolygon,
						 GraphicalEffectFactory *graphicalEffectFactory,
						 const GraphicalTextureSet *textureSet)
		: TexturedGraphicalEntity{location, basePolygon, graphicalEffectFactory, textureSet}, location{location}
{}


void LocationGraphicalEntity::setDirection(const BS::Graphic::Direction &direction)
{
	TexturedGraphicalEntity::setDirection(
			textureSet->getNumDirections() != 8 ? BS::Graphic::Direction::Invalid : direction);
}


ImageMetaData LocationGraphicalEntity::getImageMetaData() const
{
	ImageMetaData metaData;

	metaData.direction = direction;
	metaData.state = BS::State::Idle;
	metaData.weapon = BS::ItemType::Invalid;
	metaData.frame = location->getFrame();

	return metaData;
}

