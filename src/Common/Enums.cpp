/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Enums.hpp"
#include <QtCore>

//TODO change to hashmaps

static const QMap <BS::State, QString> stateToString {
	{BS::State::Idle, "Idle"},
	{BS::State::Run, "Run"},
	{BS::State::Shoot, "Shoot"},
};

static const QMap <BS::Type, QString> typeToString {
	{BS::Type::Invalid, "invalid"},
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
		BS::State result = BS::State::Idle;
		if (str == "Run") {
			result = BS::State::Run;
		} else if (str == "Shooting") {
			result = BS::State::Shoot;
		}

		return result;
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
