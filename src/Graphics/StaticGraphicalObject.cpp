/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/StaticGraphicalObject.hpp"


StaticGraphicalObject::StaticGraphicalObject(const Object* object): GraphicalObject(object)
{
	// FIXME this is just temporary for testing
	circle.setPointCount(30);
	auto position = object->getPosition();
	circle.setPosition(position.x(), position.y());
	circle.setRadius(10);
	circle.setFillColor(sf::Color::Green);
}


sf::Drawable *StaticGraphicalObject::getDrawable()
{
	return &circle;
}
