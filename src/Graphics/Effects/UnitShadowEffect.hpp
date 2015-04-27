/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Graphics/Effects/GraphicalEffect.hpp"


class UnitShadowEffect : public GraphicalEffect {
public:
	UnitShadowEffect(const Viewport *viewport);
	void draw (const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget) override;
	int getOrderId() const override;

private:
	sf::Sprite sprite;
};
