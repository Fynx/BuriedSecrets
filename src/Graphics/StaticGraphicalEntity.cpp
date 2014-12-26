/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/StaticGraphicalEntity.hpp"


using namespace sf;


StaticGraphicalEntity::StaticGraphicalEntity(const Object* object, const Texture *texture)
	: SpriteGraphicalEntity{object}
{
	sprite.setTexture(*texture);
}


void StaticGraphicalEntity::setDirection(const BS::Graphic::Direction &direction)
{
	// FIXME Not supported. Do we wan't to support it in any way?
}


void StaticGraphicalEntity::update(const float timeDelta)
{}

