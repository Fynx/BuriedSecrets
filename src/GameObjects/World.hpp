/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Location.hpp"
#include "GameObjects/Object.hpp"

class World : public Object, public Location {
public:
	World(const Prototype *prototype);
};