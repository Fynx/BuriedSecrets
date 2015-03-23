/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "GameObjects/Environment.hpp"
#include "Graphics/Entities/TexturedGraphicalEntity.hpp"


class EnvironmentGraphicalEntity : public TexturedGraphicalEntity {
public:
	EnvironmentGraphicalEntity(const Environment *environmentObject, const QList<QPointF> &basePolygon,
				   GraphicalEffectFactory *graphicalEffectFactory,
				   const GraphicalTextureSet *textureSet);

	void update(const float timeDelta) override;

protected:
	ImageMetaData getImageMetaData() const override;

	const Environment *environmentObject;
};