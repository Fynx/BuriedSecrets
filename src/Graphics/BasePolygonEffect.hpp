/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once


#include "Graphics/GraphicalEffect.hpp"


class BasePolygonEffect: public GraphicalEffect {
public:
	BasePolygonEffect();
	void draw(const GraphicalEntity *graphicalEntity, const QPointF &entityPosition, const Viewport *viewport,
		  sf::RenderTarget *renderTarget) override;
	int getOrderId() const override;

private:
	sf::ConvexShape polygon;
	sf::CircleShape point;
};