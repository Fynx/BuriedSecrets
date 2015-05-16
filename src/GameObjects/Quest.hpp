/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

using namespace BS;

/**
 * @struct
 * Storage structure for Quest conditions.
 */
struct Condition
{
	ConditionType type;
	bool isNegative;
	int argument;

	void loadFromJson(const QJsonObject &json);
	QJsonObject saveToJson() const;
};

class Mind;

/**
 * @class Quest
 * Represents quests in the game.
 * Contains Conditions for activating and deactivating and convenience functions for evaluating Conditions.
 */
class Quest : public Object {
public:
	Quest(const Prototype *prototype);

	virtual Type getType() const;

	QString getTitle() const;

	bool isFinal() const;
	const QList<Condition> &getStartConds() const;
	const QList<Condition> &getFailConds() const;
	const QList<Condition> &getSuccessConds() const;

	/** Corresponding JournalEntries. */
	const int getStartEntry() const;
	const int getSuccessEntry() const;
	const int getFailEntry() const;

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

	/** Static functions for evaluating Conditions, depending on the current game state. */
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
	QString title;
	bool finalQuest;
	QList<Condition> startConds;
	QList<Condition> successConds;
	QList<Condition> failConds;
	int startEntry, failEntry, successEntry;
};
