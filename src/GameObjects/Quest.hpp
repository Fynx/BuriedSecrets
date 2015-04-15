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

class Quest : public Object {
public:
	Quest(const Prototype *prototype);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

	static bool evaluateConditions(const QList<Condition> &cond);
	static bool evaluateQuestSuccess(const Condition &);
	static bool evaluateQuestFail(const Condition &);
	static bool evaluateFoodCount(const Condition &);
	static bool evaluateTimeCount(const Condition &);
	static bool evaluateFragsCount(const Condition &);
	static bool evaluateItemFound(const Condition &);
	static bool evaluateUnitMet(const Condition &);
	static bool evaluateObjectVisible(const Condition &);
	static bool evaluateLocationReached(const Condition &);

private:
	QList<Condition> startConds;
	QList<Condition> successConds;
	QList<Condition> failConds;
	int startEntry, failEntry, successEntry;
};
