/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Equipment.hpp"

class Unit : public Object {
public:
	Unit(const Prototype *prototype);

	Object::Type getType() const;

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

private:
	int hp;
	int psychosis;
	Equipment *equipment;
};