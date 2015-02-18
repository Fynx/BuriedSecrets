/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Equipment.hpp"
#include "GameObjects/Location.hpp"
#include "Common/Enums.hpp"

class Unit : public Object {
public:
	Unit(const Prototype *prototype);

	BS::Type getType() const;

	Item *getUsedItem();
	Equipment *getEquipment();
	void setEquipment(Equipment *eq);
	int getEquipmentUid() const;

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
	int getAttack() const;

	/** Action-wise */

	void setCommand(BS::Command c);
	BS::Command getCommand();

	QList<QPointF> &getCurrentPath();
	void setCurrentPath(const QList<QPointF> &path);

	int getTargetObject() const;
	void setTargetObject(int uid);

	QPointF getTargetPoint();
	void setTargetPoint(QPointF);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	Location *location;

	int hp;
	int psychosis;
	BS::Command command;
	Equipment *equipment;
	int equipmentUid;

	QList<QPointF> currentPath;

	int targetObjectUid;
	QPointF targetPoint;
};
