/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "GameObjects/Object.hpp"


/**
 * @brief The graphical representation of the logical object.
 *
 */
class GraphicalEntity {
public:
	GraphicalEntity(const Object *object);
	virtual ~GraphicalEntity();

	virtual sf::Drawable *getDrawable() = 0;
	/**
	 * @brief Sets the Entity's position.
	 * Units to be decided (probably pixels, TODO).
	 *
	 * @param position In some units...
	 */
	virtual void setPosition(const QPointF& position) = 0;
	const Object* getObject() const;
	/**
	 * @brief Updates the internal state of the Entity over the time that has passed since the last update.
	 *
	 * @param timeDelta Time since the last update (in ms).
	 * @return void
	 */
	virtual void update(const float timeDelta) = 0;

private:
	const Object *object;
};