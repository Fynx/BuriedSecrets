/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Equipment.hpp"
#include "GameObjects/Location.hpp"

class Unit : public Object {
public:
	Unit(const Prototype *prototype);

	Object::Type getType() const;

	Location *getLocation();
	void setLocation(Location *location);

	int getHP() const;
	void setHP(int hp);
	int getMaxHP() const;

	int getPsychosis() const;
	void setPsychosis(int psychosis);
	int getMaxPsychosis() const;

	int getEncumbrance() const;
	int getMaxEncumbrance() const;

	int getFoodDemand() const;

	int getSightRange() const;

	void addItem(Item *item);
	void removeItem(Item *item);

	/** Skills */

	int getDamageControl() const;
	int getEngineering() const;
	int getHealing() const;
	int getPerception() const;
	int getShooting() const;

	/** Action-wise */

	QList<QPointF> getCurrentPath() const;
	void setCurrentPath(const QList<QPointF> &path);

	int getAttackedUnitUid() const;
	void setAttackedUnitUid(int uid);

private:
	Location *location;

	int hp;
	int psychosis;
	Equipment *equipment;

	Item *armor;
	Item *medicalKit;
	Item *optics;
	Item *tools;
	Item *weapon;

	QList<QPointF> currentPath;

	int attackedUnitUid;
};