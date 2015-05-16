/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Equipment.hpp"
#include "GameObjects/Location.hpp"
#include "Common/Enums.hpp"

/**
 * @class Unit
 * An Object visible on the map.
 * Units can move, attack, enter and leave Locations, use Items.
 * Every Unit belongs to some Faction.
 */
class Unit : public Object, public Equipped {
public:
	Unit(const Prototype *prototype);
	virtual ~Unit();

	BS::Type getType() const;

	Item *getUsedItem() const;

	Location *getLocation() const;
	void setLocation(Location *location);

	float getHP() const;
	void setHP(int hp);
	float getMaxHP() const;

	/** Unit mental health. */
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

	void setAttitude(BS::Attitude a);
	BS::Attitude getAttitude() const;

	void setCommand(BS::Command c);
	BS::Command getCommand();

	QList<QPointF> &getCurrentPath();
	const QList<QPointF> getCurrentPath() const;
	void setCurrentPath(const QList<QPointF> &path);

	QVector<QPointF> getPatrolRoute() const;
	void setPatrolRoute(const QVector<QPointF> &route);

	int getTargetObject() const;
	void setTargetObject(int uid);

	QPointF getTargetPoint();
	void setTargetPoint(QPointF);

	float getTargetAngle();
	void setTargetAngle(float);

	const Object *getNearestEnemy() const;
	void setNearestEnemy(const Object *);

	int getFrags() const;
	void incFrags();

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	Location *location;

	int hp;
	int psychosis;
	BS::Command command;
	BS::Attitude attitude;

	QList<QPointF> currentPath;
	QVector<QPointF> patrolRoute;

	int targetObjectUid;
	QPointF targetPoint;
	float targetAngle;
	const Object *nearestEnemy;
	int frags;
};
