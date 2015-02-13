/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once


#include "Graphics/Effect.hpp"


class BasePolygonEffect: public Effect {
public:
	void draw(const GraphicalEntity *graphicalEntity, const QPointF &entityPosition, sf::RenderTarget *renderTarget) override;
	int getOrderId() const override;

private:
	sf::ConvexShape polygon;
};