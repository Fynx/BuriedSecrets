/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

class EffectData;
class GraphicalTextureSet;
class QRectF;
class Viewport;

namespace sf {
	class RenderTexture;
};


/**
 * @brief A class that represents a reusable decal hat can draw itself on a texture.
 */
class Decal {
public:
	Decal(const Viewport *viewport, const GraphicalTextureSet *decalTextureSet);
	virtual void draw(sf::RenderTexture &renderTarget, const EffectData *effectData) = 0;
	/**
	 * @brief Returns the bounds of the area that will be affected by the decal.
	 */
	virtual QRectF getTargetRect(const EffectData *effectData) = 0;

protected:
	const Viewport* viewport;
	const GraphicalTextureSet *decalTextureSet;
};
