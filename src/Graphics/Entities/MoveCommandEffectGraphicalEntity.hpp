/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Graphics/Entities/EffectGraphicalEntity.hpp"


/**
 * @brief This EffectGraphicalEntity represents a marker for the move command target.
 */
class MoveCommandEffectGraphicalEntity: public EffectGraphicalEntity {
public:
	MoveCommandEffectGraphicalEntity(const Viewport *viewport, const sf::Texture *texture);
	void draw(sf::RenderTarget *renderTarget) override;
	void update(const float timeDelta) override;
	void updateData(const EffectData *effectData) override;

private:
	sf::Sprite sprite;
};
