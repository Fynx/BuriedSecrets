/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Building.hpp"

Building::Building(const Prototype *prototype)
	: Object(prototype)
{}

Object::Type Building::getType() const
{
	return Object::Type::Building;
}

QDataStream &operator<<(QDataStream &out, const Building &building)
{
	out << dynamic_cast<const Object &>(building);
	return out;
}

QDataStream &operator>>(QDataStream &in, Building &building)
{
	in >> dynamic_cast<Object &>(building);
	return in;
}
