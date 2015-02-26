/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Enums.hpp"
#include "Common/Strings.hpp"
#include <QtCore>

//TODO change to hashmaps

static const QMap<BS::State, QString> stateToString {
	{BS::State::Attack,    States::Attack},
	{BS::State::Delay,     States::Delay},
	{BS::State::Idle,      States::Idle},
	{BS::State::Inside,    States::Inside},
	{BS::State::Heal,      States::Heal},
	{BS::State::RunAttack, States::RunAttack},
	{BS::State::Run,       States::Run},
	{BS::State::Shoot,     States::Shoot},
};

static const QMap<BS::Type, QString> typeToString {
	{BS::Type::Invalid,   Types::Invalid},
	{BS::Type::Item,      Types::Item},
	{BS::Type::Equipment, Types::Equipment},
	{BS::Type::Faction,   Types::Faction},
	{BS::Type::Journal,   Types::Journal},
	{BS::Type::Location,  Types::Location},
	{BS::Type::Unit,      Types::Unit},
};

static const QMap<BS::Slot, QString> slotToString {
	{BS::Slot::Armor,          Slots::Armor},
	{BS::Slot::Invalid,        Slots::Invalid},
	{BS::Slot::Fortification,  Slots::Fortification},
	{BS::Slot::Medicament,     Slots::Medicament},
	{BS::Slot::Perception,     Slots::Perception},
	{BS::Slot::Tool,           Slots::Tool},
	{BS::Slot::Weapon,         Slots::Weapon},
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
		return ::slotToString.value(slot, Slots::Invalid);
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
		return ::stateToString.value(state, States::Invalid);
	}

	QString changeTypeToString(BS::Type type)
	{
		return ::typeToString.value(type, Types::Invalid);
	}

	BS::Type changeStringToType(const QString &string)
	{
		return ::typeToString.key(string, BS::Type::Invalid);
	}
}
