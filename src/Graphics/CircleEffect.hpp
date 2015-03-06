/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "Graphics/GraphicalEffect.hpp"


class CircleEffect: public GraphicalEffect {
public:
	CircleEffect(const Viewport *viewport, const sf::Color &outlineColor,
		     const sf::Color &fillColor = sf::Color::Transparent);
	void draw(const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget) override;
	virtual int getOrderId() const = 0;
	/**
	 * @brief A hook for the subclass to implement any logic updating the circle.
	 *
	 * Called after establishing the scale but before drawing.
	 */
	virtual void update(const GraphicalEntity *graphicalEntity) = 0;

	constexpr static float PointsPerPixel = 0.06;	// How many points the circle should have per one pixel
							// of length.

protected:
	void setGeometry(const QPointF &position, const float radius);
	void setOutlineThickness(const float thickness);

private:
	sf::CircleShape circleShape;
};