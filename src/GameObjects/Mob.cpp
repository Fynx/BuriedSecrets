/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Mob.hpp"

Mob::Mob(const Prototype *prototype)
	: Object(prototype)
{}

Object::Type Mob::getType() const
{
	return Object::Type::Mob;
}
