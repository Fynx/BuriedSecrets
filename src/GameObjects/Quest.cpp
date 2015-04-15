/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Quest.hpp"
#include "Mind/Mind.hpp"

Quest::Quest(const Prototype *prototype)
	: Object(prototype),
	  finalQuest(false),
	  startEntry(0),
	  failEntry(0),
	  successEntry(0)
{
	setState(State::Inactive);
}


bool Quest::isFinal() const
{
	return finalQuest;
}

const QList<Condition> &Quest::getFailConds() const
{
	return failConds;
}


const QList<Condition> &Quest::getStartConds() const
{
	return startConds;
}


const QList<Condition> &Quest::getSuccessConds() const
{
	return successConds;
}


const int Quest::getFailEntry() const
{
	return failEntry;
}


const int Quest::getSuccessEntry() const
{
	return successEntry;
}


const int Quest::getStartEntry() const
{
	return startEntry;
}


void Quest::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
}


QJsonObject Quest::saveToJson() const
{
	return Object::saveToJson();
}


bool Quest::evaluateConditions(const QList<Condition> &cond, Mind *mind, int factionId)
{
	bool res = true;
	for (Condition c : cond){
		switch (c.type){
		case ConditionType::QuestSuccess:
			res = res && evaluateQuestSuccess(c, mind, factionId);
			break;
		case ConditionType::QuestFail:
			res = res && evaluateQuestFail(c, mind, factionId);
			break;
		case ConditionType::FoodCount:
			res = res && evaluateFoodCount(c, mind, factionId);
			break;
		case ConditionType::TimeCount:
			res = res && evaluateTimeCount(c, mind, factionId);
			break;
		case ConditionType::FragsCount:
			res = res && evaluateFragsCount(c, mind, factionId);
			break;
		case ConditionType::ItemFound:
			res = res && evaluateItemFound(c, mind, factionId);
			break;
		case ConditionType::UnitMet:
			res = res && evaluateUnitMet(c, mind, factionId);
			break;
		case ConditionType::ObjectVisible:
			res = res && evaluateObjectVisible(c, mind, factionId);
			break;
		case ConditionType::LocationReached:
			res = res && evaluateLocationReached(c, mind, factionId);
			break;
		default:
			break;
		}
	}

	return res;
}


bool Quest::evaluateFoodCount(const Condition &c, Mind *mind, int factionId)
{
	return true;
}


bool Quest::evaluateFragsCount(const Condition &c, Mind *mind, int factionId)
{
	return true;
}


bool Quest::evaluateItemFound(const Condition &c, Mind *mind, int factionId)
{
	return true;
}


bool Quest::evaluateLocationReached(const Condition &c, Mind *mind, int factionId)
{
	return true;
}


bool Quest::evaluateObjectVisible(const Condition &c, Mind *mind, int factionId)
{
	return true;
}


bool Quest::evaluateQuestFail(const Condition &c, Mind *mind, int factionId)
{
	return true;
}


bool Quest::evaluateQuestSuccess(const Condition &c, Mind *mind, int factionId)
{
	return true;
}


bool Quest::evaluateTimeCount(const Condition &c, Mind *mind, int factionId)
{
	return true;
}


bool Quest::evaluateUnitMet(const Condition &c, Mind *mind, int factionId)
{
	return true;
}
