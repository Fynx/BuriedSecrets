/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class Location : public Object {
public:
	Location(const Prototype *prototype);
	virtual ~Location();
};
