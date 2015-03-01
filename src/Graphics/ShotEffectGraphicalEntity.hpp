/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "Graphics/EffectGraphicalEntity.hpp"
#include "Graphics/LineShape.hpp"
#include "Mind/PointToPointEffectData.hpp"


/**
 * @brief This class is a graphical representation of shot effect. It's one of the global effects.
 */
class ShotEffectGraphicalEntity : public EffectGraphicalEntity {
public:
	ShotEffectGraphicalEntity(const Viewport *viewport);
	void draw(sf::RenderTarget *renderTarget) override;
	void update(const float timeDelta) override;
	void updateData(const EffectData *effectData) override;

private:
	LineShape line;
	// TODO hit or miss
};