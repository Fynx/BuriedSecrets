/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Enums.hpp"
#include <QtCore>

//TODO change to hashmaps

static const QMap <BS::State, QString> stateToString {
	{BS::State::Idle, "Idle"},
	{BS::State::Attack, "Attack"},
	{BS::State::RunAttack, "RunAttack"},
	{BS::State::Run, "Run"},
	{BS::State::Heal, "Heal"},
	{BS::State::Inside, "Inside"},
	{BS::State::Shoot, "Shoot"},
	{BS::State::Delay, "Delay"},
};

static const QMap <BS::Type, QString> typeToString {
	{BS::Type::Invalid, "invalid"},
	{BS::Type::Item, "item"},
	{BS::Type::Building, "building"},
	{BS::Type::Camp, "camp"},
	{BS::Type::Equipment, "equipment"},
	{BS::Type::Faction, "faction"},
	{BS::Type::Fortification, "fortification"},
	{BS::Type::Journal, "journal"},
	{BS::Type::Mob, "mob"},
	{BS::Type::Unit, "unit"},
};

namespace BS {

	State getStateFromString(const QString &str)
	{
		return ::stateToString.key(str, BS::State::Idle);
	}

	QString changeTypeToString(BS::Type type)
	{
		return ::typeToString.value(type, QString());
	}

	BS::Type changeStringToType(const QString &string)
	{
		return ::typeToString.key(string, BS::Type::Invalid);
	}

}
