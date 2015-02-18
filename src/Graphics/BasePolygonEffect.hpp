/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once


#include "Graphics/Effect.hpp"


class BasePolygonEffect: public Effect {
public:
	BasePolygonEffect();
	void draw(const GraphicalEntity *graphicalEntity, const QPointF &entityPosition, const Viewport *viewport,
		  sf::RenderTarget *renderTarget) override;
	int getOrderId() const override;

private:
	sf::ConvexShape polygon;
	sf::CircleShape point;
};