/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "Graphics/Effects/GraphicalEffect.hpp"


class BasePolygonEffect: public GraphicalEffect {
public:
	BasePolygonEffect(const Viewport *viewport);
	void draw(const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget) override;
	int getOrderId() const override;

private:
	sf::ConvexShape polygon;
	sf::CircleShape point;
};