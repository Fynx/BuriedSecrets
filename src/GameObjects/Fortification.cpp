#include "GameObjects/Fortification.hpp"

Fortification::Fortification(const Prototype *prototype)
	: Object(prototype)
{}

Object::Type Fortification::getType() const
{
	return Object::Type::Fortification;
}

QDataStream &operator<<(QDataStream &out, const Fortification &fortification)
{
	out << dynamic_cast<const Object &>(fortification);
	return out;
}

QDataStream &operator>>(QDataStream &in, Fortification &fortification)
{
	in >> dynamic_cast<Object &>(fortification);
	return in;
}
