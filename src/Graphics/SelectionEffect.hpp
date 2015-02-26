/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <SFML/Graphics.hpp>

#include "GraphicalEffect.hpp"


class SelectionEffect: public GraphicalEffect {
public:
	SelectionEffect();
	void draw(const GraphicalEntity *graphicalEntity, const QPointF &entityPosition, const Viewport *viewport,
		  sf::RenderTarget *renderTarget) override;
	int getOrderId() const override;

private:
	sf::CircleShape circleShape;
	QList<QPointF> basePolygon;
};