/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Equipment.hpp"
#include "GameObjects/Location.hpp"

class Unit : public Object {
public:
	Unit(const Prototype *prototype);

	BS::Type getType() const;

	Location *getLocation();
	void setLocation(Location *location);

	float getHP() const;
	void setHP(int hp);
	float getMaxHP() const;

	float getPsychosis() const;
	void setPsychosis(int psychosis);
	float getMaxPsychosis() const;

	float getEncumbrance() const;
	float getMaxEncumbrance() const;

	float getFoodDemand() const;

	float getSightRange() const;

	float getSpeed() const;

	float getRegeneration() const;

	void addItem(Item *item);
	void removeItem(Item *item);

	/** Skills */

	float getDamageControl() const;
	int getEngineering() const;
	int getHealing() const;
	int getPerception() const;
	int getShooting() const;

	/** Action-wise */

	QList<QPointF> &getCurrentPath();
	void setCurrentPath(const QList<QPointF> &path);

	int getAttackedUnitUid() const;
	void setAttackedUnitUid(int uid);

private:
	friend QDataStream &operator<<(QDataStream &out, const Unit &object);
	friend QDataStream &operator>>(QDataStream &in, Unit &object);
	//TODO all pointers to objects change to uid

	Location *location;

	int hp;
	int psychosis;
	Equipment *equipment;

	// Should be implemented inside equipment
	Item *armor;
	Item *medicalKit;
	Item *optics;
	Item *tools;
	Item *weapon;

	QList<QPointF> currentPath;

	int attackedUnitUid;
};
