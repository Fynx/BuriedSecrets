/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class Character : public Object {
public:
	Character(const Prototype *prototype);

	Object::Type getType() const;
};