/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

using namespace BS;

struct Condition
{
	ConditionType type;
	bool isNegative;
	int argument;
};

class Mind;

class Quest : public Object {
public:
	Quest(const Prototype *prototype);

	bool isFinal() const;
	const QList<Condition> &getStartConds() const;
	const QList<Condition> &getFailConds() const;
	const QList<Condition> &getSuccessConds() const;

	const int getStartEntry() const;
	const int getSuccessEntry() const;
	const int getFailEntry() const;

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

	static bool evaluateConditions(const QList<Condition> &cond, Mind *mind, int factionId);
	static bool evaluateQuestSuccess(const Condition &c, Mind *mind, int factionId);
	static bool evaluateQuestFail(const Condition &c, Mind *mind, int factionId);
	static bool evaluateFoodCount(const Condition &c, Mind *mind, int factionId);
	static bool evaluateTimeCount(const Condition &c, Mind *mind, int factionId);
	static bool evaluateFragsCount(const Condition &c, Mind *mind, int factionId);
	static bool evaluateItemFound(const Condition &c, Mind *mind, int factionId);
	static bool evaluateUnitMet(const Condition &c, Mind *mind, int factionId);
	static bool evaluateObjectVisible(const Condition &c, Mind *mind, int factionId);
	static bool evaluateLocationReached(const Condition &c, Mind *mind, int factionId);

private:
	bool finalQuest;
	QList<Condition> startConds;
	QList<Condition> successConds;
	QList<Condition> failConds;
	int startEntry, failEntry, successEntry;
};
