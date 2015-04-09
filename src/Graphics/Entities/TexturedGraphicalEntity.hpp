/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Graphics/Entities/SpriteGraphicalEntity.hpp"

class ImageMetaData;
class GraphicalTextureSet;


/**
 * @brief This is a common abstract base for all textured graphical entities. It assumes that all textures for an
 * entity are passed to it on creation.
 */
class TexturedGraphicalEntity : public SpriteGraphicalEntity {
public:
	TexturedGraphicalEntity(const Object *object, const QList<QPointF> &basePolygon,
				GraphicalEffectFactory *graphicalEffectFactory, const GraphicalTextureSet *textureSet);
	void setDirection(const BS::Graphic::Direction &direction) override;
	void update(const float timeDelta) override;

protected:
	virtual ImageMetaData getImageMetaData() const = 0;

	BS::Graphic::Direction direction;

	const GraphicalTextureSet *textureSet;
};