/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Graphics/Decals/Decal.hpp"


/**
 * @brief This class represents a decal for the blood splatter.
 */
class BloodDecal: public Decal {
public:
	BloodDecal(const Viewport *viewport, const GraphicalTextureSet *decalTextureSet);
	void draw(sf::RenderTexture &renderTarget, const EffectData *effectData) override;
	QRectF getTargetRect(const EffectData *effectData) override;
};
