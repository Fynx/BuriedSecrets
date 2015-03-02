/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "Graphics/GraphicalEffect.hpp"


class SelectionEffect: public GraphicalEffect {
public:
	SelectionEffect(const Viewport *viewport, const sf::Color &color);
	void draw(const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget) override;
	int getOrderId() const override;

private:
	sf::CircleShape circleShape;
	QList<QPointF> basePolygon;
};