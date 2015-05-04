/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Quest.hpp"
#include "Mind/Mind.hpp"
#include "GameObjects/Location.hpp"
#include "Unit.hpp"

Quest::Quest(const Prototype *prototype)
	: Object(prototype),
	  finalQuest(false),
	  startEntry(0),
	  failEntry(0),
	  successEntry(0)
{
	setState(State::Inactive);
}

Type Quest::getType() const
{
	return BS::Type::Quest;
}

QString Quest::getTitle() const
{
	return title;
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

	auto fromJson = [](const QJsonArray &json) -> QList<Condition> {
		QList<Condition> conds;
		for (const QJsonValue &val : json) {
			Condition cond;
			cond.loadFromJson(val.toObject());
			conds.append(cond);
		}
		return conds;
	};

	Q_ASSERT(json.contains(Attributes::Title));

	title      = json[Attributes::Title].toString();
	finalQuest = json[Attributes::IsFinal].toBool();

	startConds   = fromJson(json[Attributes::StartConditions].toArray());
	successConds = fromJson(json[Attributes::SuccessConditions].toArray());
	failConds    = fromJson(json[Attributes::FailureConditions].toArray());

	startEntry   = json[Attributes::StartEntry].toInt();
	failEntry    = json[Attributes::FailureEntry].toInt();
	successEntry = json[Attributes::SuccessEntry].toInt();
}

QJsonObject Quest::saveToJson() const
{
	auto toJson = [](const QList<Condition> &conds) -> QJsonArray {
		QJsonArray json;
		for (const Condition &cond : conds)
			json.append(cond.saveToJson());
		return json;
	};

	QJsonObject json = Object::saveToJson();

	json[Attributes::Title]   = title;
	json[Attributes::IsFinal] = finalQuest;

	json[Attributes::StartConditions]   = toJson(startConds);
	json[Attributes::SuccessConditions] = toJson(successConds);
	json[Attributes::FailureConditions] = toJson(failConds);

	json[Attributes::StartEntry]   = startEntry;
	json[Attributes::FailureEntry] = failEntry;
	json[Attributes::SuccessEntry] = successEntry;

	return json;
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
	bool res = mind->getFactionById(factionId)->getFood() > c.argument;

	return res ^ c.isNegative;
}

bool Quest::evaluateFragsCount(const Condition &c, Mind *mind, int factionId)
{
	QSet<int> units = mind->getFactionById(factionId)->getUnitsUids();
	int frags = 0;
	for (int unit : units)
		frags += static_cast<Unit *>(mind->getObjectFromUid(unit))->getFrags();
	bool res = frags >= c.argument;
	return res ^ c.isNegative;
}

bool Quest::evaluateItemFound(const Condition &c, Mind *mind, int factionId)
{
	bool res = mind->getFactionById(factionId)->getEquipment()->getItemsUids().contains(c.argument);
	return res ^ c.isNegative;
}

bool Quest::evaluateLocationReached(const Condition &c, Mind *mind, int factionId)
{
	Location *loc = dynamic_cast<Location*>(mind->getObjectFromUid(c.argument));
	if (!loc)
		return true;
	return (loc->getFactionId() == factionId) ^ c.isNegative;
}

bool Quest::evaluateObjectVisible(const Condition &c, Mind *mind, int factionId)
{
	return true;
}

bool Quest::evaluateQuestFail(const Condition &c, Mind *mind, int factionId)
{
	Quest *quest = dynamic_cast<Quest *>(mind->getObjectFromUid(c.argument));
	if (!quest)
		return true;
	return (quest->getState() == State::Fail) ^ c.isNegative;
}

bool Quest::evaluateQuestSuccess(const Condition &c, Mind *mind, int factionId)
{
	Quest *quest = dynamic_cast<Quest *>(mind->getObjectFromUid(c.argument));
	if (!quest)
		return true;
	return (quest->getState() == State::Success) ^ c.isNegative;
}

bool Quest::evaluateTimeCount(const Condition &c, Mind *mind, int factionId)
{
	return true;
}

bool Quest::evaluateUnitMet(const Condition &c, Mind *mind, int factionId)
{
	bool res = mind->getFactionById(factionId)->getUnitsUids().contains(c.argument);
	return res ^ c.isNegative;
}


void Condition::loadFromJson(const QJsonObject &json)
{
	Q_ASSERT(json.contains(Attributes::ConditionType));
	type = BS::changeStringToConditionType(json[Attributes::ConditionType].toString());
	if (type == BS::ConditionType::Invalid)
		warn("Invalid condition type.");

	isNegative = json[Attributes::IsNegative].toBool();
	argument   = json[Attributes::Argument].toInt();
}

QJsonObject Condition::saveToJson() const
{
	QJsonObject json;

	json[Attributes::ConditionType] = BS::changeConditionTypeToString(type);
	if (isNegative)
		json[Attributes::IsNegative] = isNegative;
	json[Attributes::Argument] = argument;

	return json;
}
