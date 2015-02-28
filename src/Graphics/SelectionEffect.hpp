/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <SFML/Graphics.hpp>

#include "Graphics/GraphicalEffect.hpp"


class SelectionEffect: public GraphicalEffect {
public:
	// We don't use the EffectData as we already have the object from the entity when drawing.
	SelectionEffect(const Viewport *viewport);
	void draw(const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget) override;
	int getOrderId() const override;

private:
	sf::CircleShape circleShape;
	QList<QPointF> basePolygon;
};