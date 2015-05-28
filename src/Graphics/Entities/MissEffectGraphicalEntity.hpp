/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Graphics/Entities/EffectGraphicalEntity.hpp"

class GraphicalTextureSet;


/**
 * @brief This EffectGraphicalEntity represents a Object-unrelated effect for a missed shot.
 */
class MissGraphicalEntity: public EffectGraphicalEntity {
public:
	MissGraphicalEntity(const Viewport *viewport, const GraphicalTextureSet *missTextureSet);
	void draw (sf::RenderTarget *renderTarget) override;
	void update (const float timeDelta) override;
	void updateData (const EffectData *effectData) override;

private:
	sf::Sprite sprite;
	const GraphicalTextureSet *missTextureSet;
};
