/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicalEntity.hpp"


GraphicalEntity::GraphicalEntity(const Object* object)
	: object{object}
{}


GraphicalEntity::~GraphicalEntity()
{}


const Object *GraphicalEntity::getObject() const
{
	return object;
}

