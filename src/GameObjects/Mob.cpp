/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Mob.hpp"

Mob::Mob(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Mob::getType() const
{
	return BS::Type::Mob;
}
