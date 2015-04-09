/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Graphics/Entities/TexturedGraphicalEntity.hpp"

class Unit;


class UnitGraphicalEntity : public TexturedGraphicalEntity {
public:
	UnitGraphicalEntity(const Unit *unit, const QList<QPointF> &basePolygon,
			    GraphicalEffectFactory *graphicalEffectFactory, const GraphicalTextureSet *textureSet);

protected:
	ImageMetaData getImageMetaData() const override;

private:
	const Unit *unit;
};