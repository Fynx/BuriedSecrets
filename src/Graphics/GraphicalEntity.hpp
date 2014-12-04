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

private:
	const Object *object;
};