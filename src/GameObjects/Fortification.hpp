/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class Fortification : public Object {
public:
	Fortification(const Prototype *prototype);

	BS::Type getType() const;

private:
	friend QDataStream &operator<<(QDataStream &out, const Fortification &fortification);
	friend QDataStream &operator>>(QDataStream &in, Fortification &fortification);
};