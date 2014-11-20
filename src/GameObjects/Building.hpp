#pragma once

#include "DataManager/Prototype.hpp"
#include "GameObjects/Object.hpp"

class Building : public Object {
public:
	Building(const Prototype *prototype);

	Object::Type getType() const;

private:
	friend QDataStream &operator<<(QDataStream &out, const Building &building);
	friend QDataStream &operator>>(QDataStream &in, Building &building);
};