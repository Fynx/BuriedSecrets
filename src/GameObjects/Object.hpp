#pragma once

#include "DataManager/Prototype.hpp"

class Object {
public:
	Object(const Prototype *prototype);
	virtual ~Object();

	const Prototype *getPrototype();

	//TODO put it somewhere else
	enum class Type {
		Invalid,
		Building,
		Creature,
		Fortification
	};

	virtual Type getType() const = 0;

private:
	const Prototype *prototype;

	friend QDataStream &operator<<(QDataStream &out, const Object &object);
	friend QDataStream &operator>>(QDataStream &in, Object &object);
};