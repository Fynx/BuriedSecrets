/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

class GraphicalEntity;
class Viewport;


/**
 * @brief This is the base abstract class representing an effect to be drawn for some GraphicalEntity.
 */
class GraphicalEffect {
public:
	GraphicalEffect(const Viewport *viewport);
	/**
	 * @brief Draws the desired effect.
	 *
	 * @param graphicalEntity The entity for which the effect should be drawn.
	 * @param viewport The viewport used for drawing.
	 * @param renderTarget The render target to which the effect should be drawn.
	 */
	virtual ~GraphicalEffect() = default;

	virtual void draw(const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget) = 0;

	/**
	 * @brief Returns a unique id which defines the order in which the effect should be drawn if multiple effects
	 * are being drawn. The smaller the id, the earlier the effect will be drawn.
	 *
	 * @return int
	 */
	virtual int getOrderId() const = 0;

protected:
	const Viewport *viewport;
};
