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
	const QPointF &getPosition() const;
	void setPosition(const float x, const float y);

	//TODO put it somewhere else
	enum class Type {
		Invalid,
		Building,
		Fortification,
		Character,
		Mob,
	};

	virtual Type getType() const = 0;

private:
	const Prototype *prototype;
	// Dana fizyczna, wywalić stąd
	QPointF position;

	friend QDataStream &operator<<(QDataStream &out, const Object &object);
	friend QDataStream &operator>>(QDataStream &in, Object &object);
};
