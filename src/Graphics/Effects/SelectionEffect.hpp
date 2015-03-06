/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "Graphics/Effects/CircleEffect.hpp"


class SelectionEffect: public CircleEffect {
public:
	SelectionEffect(const Viewport *viewport, const sf::Color &color);
	int getOrderId() const override;
	void update(const GraphicalEntity *graphicalEntity) override;

private:
	QList<QPointF> basePolygon;
};