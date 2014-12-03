/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <SFML/Graphics.hpp>

#include "Graphics/GraphicalObject.hpp"


/**
 * @brief This class represents a static graphical object that always displays the same image.
 *
 */
class StaticGraphicalObject: public GraphicalObject {
public:
	StaticGraphicalObject(const Object* object);
	virtual sf::Drawable *getDrawable() override;

private:
	//FIXME temporary for testing
	sf::CircleShape circle;
};