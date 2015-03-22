/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Entities/UnitGraphicalEntity.hpp"

#include <cassert>

#include "DataManager/ImageMetaData.hpp"
#include "DebugManager/DebugManager.hpp"


UnitGraphicalEntity::UnitGraphicalEntity(const Unit *unit, const QList<QPointF> &basePolygon,
					 GraphicalEffectFactory *graphicalEffectFactory,
					 const GraphicalTextureSet* textureSet)
		: SpriteGraphicalEntity{unit, basePolygon, graphicalEffectFactory}, textureSet{textureSet}, unit{unit}
{}


void UnitGraphicalEntity::setDirection(const BS::Graphic::Direction &direction)
{
	this->direction = direction;
}


void UnitGraphicalEntity::update(const float timeDelta)
{
	ImageMetaData metaData;

	metaData.direction = direction;
	metaData.frame = unit->getFrame();
	metaData.state = unit->getState();
	metaData.weapon = BS::ItemType::Invalid;

	// Get the weapon type of the used item (first matching).
	const Item *item = unit->getUsedItem();
	if (item != nullptr) {
		const auto &types = item->getItemTypes();
		for (const auto& t: types) {
			if (BS::WeaponTypes.contains(t)) {
				metaData.weapon = t;
				break;
			}
		}
	}

	sprite.setTexture(*(textureSet->getFrame(metaData)));
}


