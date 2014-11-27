#pragma once
#include <SFML/Graphics.hpp>

#include "GameObjects/Object.hpp"


/**
 * @brief The graphical representation of the logical object.
 *
 */
class GraphicalObject {
public:
	GraphicalObject(const Object *object);
	sf::Drawable *getDrawable();

private:
	const Object *object;

	//FIXME temporary for testing
	sf::CircleShape circle;
};