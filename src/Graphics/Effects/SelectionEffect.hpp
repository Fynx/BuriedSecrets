/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QList>
#include <QPointF>
#include <SFML/Graphics.hpp>

#include "Graphics/Effects/CircleEffect.hpp"


/**
 * @brief This is the direct implementation of a circular effect for unit selection.
 *
 * NOTE This class can represent a selection of any given color.
 */
class SelectionEffect: public CircleEffect {
public:
	SelectionEffect(const Viewport *viewport, const sf::Color &color);
	int getOrderId() const override;
	void update(const GraphicalEntity *graphicalEntity) override;

private:
	QList<QPointF> basePolygon;
};
