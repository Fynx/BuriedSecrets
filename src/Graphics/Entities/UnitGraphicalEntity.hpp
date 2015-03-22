/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "DataManager/ImageMetaData.hpp"
#include "GameObjects/Unit.hpp"
#include "Graphics/Entities/SpriteGraphicalEntity.hpp"
#include "Graphics/GraphicalTextureSet.hpp"


class TextureSet;


class UnitGraphicalEntity : public SpriteGraphicalEntity {
public:
	UnitGraphicalEntity(const Unit *unit, const QList<QPointF> &basePolygon,
			    GraphicalEffectFactory *graphicalEffectFactory, const GraphicalTextureSet *textureSet);
	void setDirection(const BS::Graphic::Direction &direction) override;
	void update(const float timeDelta) override;

private:
	BS::Graphic::Direction direction;

	const GraphicalTextureSet *textureSet;
	const Unit *unit;
};