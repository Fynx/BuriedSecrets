/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/StaticGraphicalEntity.hpp"


using namespace sf;


StaticGraphicalEntity::StaticGraphicalEntity(const Object* object, const Texture *texture)
	: GraphicalEntity{object}, sprite{*texture}
{
	// FIXME temporary:
	sprite.setScale(0.05, 0.05);
}


sf::Drawable *StaticGraphicalEntity::getDrawable()
{
	return &sprite;
}


void StaticGraphicalEntity::setPosition(const QPointF &position)
{
	sprite.setPosition(position.x(), position.y());
}


void StaticGraphicalEntity::update(const float timeDelta)
{}


