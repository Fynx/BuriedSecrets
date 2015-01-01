/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

/**
 * Physical object. Someone can put here equipment instead of in faction if it's better.
 */
class Camp : public Object {
public:
	Camp(const Prototype *prototype);

	BS::Type getType() const;

	qreal getRange() const;

private:
	qreal range;
};