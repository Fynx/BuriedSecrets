/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Graphics/Effects/GraphicalEffect.hpp"


class GraphicalEntity;


/**
 * @brief This class represents a debug effect drawing a simple polygon to illustrate objects' base polygons.
 */
class BasePolygonEffect: public GraphicalEffect {
public:
	BasePolygonEffect(const Viewport *viewport);
	void draw(const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget) override;
	int getOrderId() const override;

private:
	sf::ConvexShape polygon;
	sf::CircleShape point;
};
