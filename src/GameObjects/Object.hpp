/* YoLoDevelopment, 2014
 * All rights reserved.
 */
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
		Equipment,
		Fortification,
		Journal,
		Unit,
		Mob,
	};

	virtual Type getType() const = 0;
	Object *getParent() const;
	void setParent(Object *object);

protected:
	const Prototype *prototype;
	Object *parent;

private:
	friend QDataStream &operator<<(QDataStream &out, const Object &object);
	friend QDataStream &operator>>(QDataStream &in, Object &object);
};
