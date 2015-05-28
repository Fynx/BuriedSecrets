/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Graphics/Entities/TexturedGraphicalEntity.hpp"

class Location;


/**
 * @brief This class represents the GraphicalEntity for a Location.
 */
class LocationGraphicalEntity : public TexturedGraphicalEntity {
public:
	LocationGraphicalEntity(const Location *location, const QList<QPointF> &basePolygon,
				GraphicalEffectFactory *graphicalEffectFactory, const GraphicalTextureSet *textureSet);
	void setDirection(const BS::Graphic::Direction &direction) override;

protected:
	ImageMetaData getImageMetaData() const override;

private:
	const Location *location;
};
