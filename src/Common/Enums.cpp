/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Enums.hpp"
#include <QtCore>

//TODO change to hashmaps

static const QMap<BS::State, QString> stateToString {
	{BS::State::Idle, "Idle"},
	{BS::State::Attack, "Attack"},
	{BS::State::RunAttack, "RunAttack"},
	{BS::State::Run, "Run"},
	{BS::State::Heal, "Heal"},
	{BS::State::Inside, "Inside"},
	{BS::State::Shoot, "Shoot"},
	{BS::State::Delay, "Delay"},
};

static const QMap<BS::Type, QString> typeToString {
	{BS::Type::Invalid, "invalid"},
	{BS::Type::Item, "item"},
	{BS::Type::Equipment, "equipment"},
	{BS::Type::Faction, "faction"},
	{BS::Type::Journal, "journal"},
	{BS::Type::Location, "location"},
	{BS::Type::Unit, "unit"},
};

static const QMap<BS::Slot, QString> slotToString {
	{BS::Slot::Invalid,        "invalid"},
	{BS::Slot::Weapon,         "weapon"},
	{BS::Slot::Tool,           "tool"},
	{BS::Slot::Medicament,     "medicament"},
	{BS::Slot::Armor,          "armor"},
	{BS::Slot::Fortification,  "fortification"},
	{BS::Slot::Perception,     "perception"},
};

static const QList<BS::Slot> slots_ {
	BS::Slot::Weapon,
	BS::Slot::Tool,
	BS::Slot::Medicament,
	BS::Slot::Armor,
	BS::Slot::Fortification,
	BS::Slot::Perception,
};

namespace BS {

	QString changeSlotToString(Slot slot)
	{
		return ::slotToString.value(slot, "Invalid Slot");
	}

	Slot changeStringToSlot(const QString &string)
	{
		return ::slotToString.key(string, Invalid);
	}

	const QList<Slot> getSlots()
	{
		return slots_;
	}

	State changeStringToState(const QString &str)
	{
		return ::stateToString.key(str, BS::State::Idle);
	}

	QString changeStateToString(BS::State state)
	{
		return ::stateToString.value(state, QString("Invalid State"));
	}

	QString changeTypeToString(BS::Type type)
	{
		return ::typeToString.value(type, QString("Invalid Type"));
	}

	BS::Type changeStringToType(const QString &string)
	{
		return ::typeToString.key(string, BS::Type::Invalid);
	}

}
