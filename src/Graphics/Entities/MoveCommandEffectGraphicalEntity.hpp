/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "Graphics/Entities/EffectGraphicalEntity.hpp"


class MoveCommandEffectGraphicalEntity : public EffectGraphicalEntity {
public:
	MoveCommandEffectGraphicalEntity(const Viewport *viewport, const sf::Texture *texture);
	void draw(sf::RenderTarget *renderTarget) override;
	void update(const float timeDelta) override;
	void updateData(const EffectData *effectData) override;

private:
	sf::Sprite sprite;
};