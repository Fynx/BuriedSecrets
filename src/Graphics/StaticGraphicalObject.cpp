/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/StaticGraphicalObject.hpp"


using namespace sf;


StaticGraphicalObject::StaticGraphicalObject(const Object* object, const Texture *texture)
: GraphicalObject{object}, sprite{*texture}
{
	auto position = object->getPosition();
	sprite.setPosition(position.x(), position.y());

	// FIXME temporary:
	sprite.setScale(0.05, 0.05);
}


sf::Drawable *StaticGraphicalObject::getDrawable()
{
	return &sprite;
}
