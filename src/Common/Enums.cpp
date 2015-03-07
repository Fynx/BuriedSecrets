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
	{BS::Type::Invalid,     Types::Invalid},
	{BS::Type::Item,        Types::Item},
	{BS::Type::Environment, Types::Environment},
	{BS::Type::Equipment,   Types::Equipment},
	{BS::Type::Faction,     Types::Faction},
	{BS::Type::Journal,     Types::Journal},
	{BS::Type::Location,    Types::Location},
	{BS::Type::Unit,        Types::Unit},
};

static const QMap<BS::Slot, QString> slotToString {
	{BS::Slot::Armor,          Slots::Armor},
	{BS::Slot::Fortification,  Slots::Fortification},
	{BS::Slot::Invalid,        Slots::Invalid},
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

static const QMap<BS::ItemType, QString> itemTypeToString {
	{BS::ItemType::Armor,         ItemTypes::Armor},
	{BS::ItemType::Fortification, ItemTypes::Fortification},
	{BS::ItemType::Invalid,       ItemTypes::Invalid},
	{BS::ItemType::Junk,          ItemTypes::Junk},
	{BS::ItemType::Medicament,    ItemTypes::Medicament},
	{BS::ItemType::Perception,    ItemTypes::Perception},
	{BS::ItemType::Tool,          ItemTypes::Tool},
	{BS::ItemType::AssaultRifle,  ItemTypes::AssaultRifle},
	{BS::ItemType::DualPistols,   ItemTypes::DualPistols},
	{BS::ItemType::Melee,         ItemTypes::Melee},
	{BS::ItemType::Pistol,        ItemTypes::Pistol},
	{BS::ItemType::Shotgun,       ItemTypes::Shotgun},
	{BS::ItemType::SniperRifle,   ItemTypes::SniperRifle},
};

static const QMap<BS::ItemType, BS::Slot> correspondingSlot {
	{BS::ItemType::Armor,         BS::Slot::Armor},
	{BS::ItemType::Fortification, BS::Slot::Fortification},
	{BS::ItemType::Invalid,       BS::Slot::Invalid},
	{BS::ItemType::Junk,          BS::Slot::Invalid},
	{BS::ItemType::Medicament,    BS::Slot::Medicament},
	{BS::ItemType::Perception,    BS::Slot::Perception},
	{BS::ItemType::Tool,          BS::Slot::Tool},
	{BS::ItemType::AssaultRifle,  BS::Slot::Weapon},
	{BS::ItemType::DualPistols,   BS::Slot::Weapon},
	{BS::ItemType::Melee,         BS::Slot::Weapon},
	{BS::ItemType::Pistol,        BS::Slot::Weapon},
	{BS::ItemType::Shotgun,       BS::Slot::Weapon},
	{BS::ItemType::SniperRifle,   BS::Slot::Weapon},
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

	QString changeStateToString(State state)
	{
		return ::stateToString.value(state, States::Invalid);
	}

	State changeStringToState(const QString &str)
	{
		return ::stateToString.key(str, State::Idle);
	}

	QString changeTypeToString(Type type)
	{
		return ::typeToString.value(type, Types::Invalid);
	}

	Type changeStringToType(const QString &string)
	{
		return ::typeToString.key(string, Type::Invalid);
	}

	QString changeItemTypeToString(ItemType type)
	{
		return ::itemTypeToString.value(type, ItemTypes::Invalid);
	}

	ItemType changeStringToItemType(const QString &str)
	{
		return ::itemTypeToString.key(str, ItemType::Invalid);
	}

	Slot getCorrespondingSlot(ItemType type)
	{
		return ::correspondingSlot[type];
	}
}
