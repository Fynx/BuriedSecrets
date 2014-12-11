/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class Quest : public Object {
public:
	Quest(const Prototype *prototype);

	QString getDescription() const;
};