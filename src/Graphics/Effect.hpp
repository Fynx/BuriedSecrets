/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once


#include <SFML/Graphics.hpp>

#include "Graphics/GraphicalEntity.hpp"
#include "UserInterface/Viewport.hpp"


/**
 * @brief This is the base abstract class representing an effect to be drawn for some GraphicalEntity.
 *
 * By design, the whole tree of Effect classes is supposed to contain mostly behaviours, less likely any object-specific
 * data (sort of like Animators).
 *
 */
class Effect {
public:
	/**
	 * @brief Draws the desire effect.
	 *
	 * Please note that this method can even decide to not draw anything.
	 *
	 * @param graphicalEntity The entity for which the effect should be drawn.
	 * @param entityPosition The position at which the upper left corner of the target entity will be drawn.
	 * @param viewport The viewport used for drawing.
	 * @param renderTarget The render target to which the effect should be drawn.
	 */
	virtual void draw(const GraphicalEntity *graphicalEntity, const QPointF &entityPosition,
			  const Viewport *viewport, sf::RenderTarget *renderTarget) = 0;

	/**
	 * @brief Returns a unique id which defines the order in which the effect should be drawn if multiple effects
	 * are being drawn. The smaller the id, the earlier the effect will be drawn.
	 *
	 * @return int
	 */
	virtual int getOrderId() const = 0;

	virtual ~Effect() {}
};