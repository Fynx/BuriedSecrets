/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Character.hpp"

Character::Character(const Prototype *prototype)
	: Object(prototype)
{}

Object::Type Character::getType() const
{
	return Object::Type::Character;
}
