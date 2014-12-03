/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class Mob : public Object {
public:
	Mob(const Prototype *prototype);

	Object::Type getType() const;
};