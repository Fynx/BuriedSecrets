#include "Graphics/GraphicalObject.hpp"


GraphicalObject::GraphicalObject(const Object* object)
	: object{object}
{
	// FIXME this is just temporary for testing
	circle.setPointCount(30);
	auto position = object->getPosition();
	circle.setPosition(position.x(), position.y());
	circle.setRadius(10);
	circle.setFillColor(sf::Color::Green);
}


sf::Drawable *GraphicalObject::getDrawable()
{
	// FIXME temporary.
	return &circle;
}

