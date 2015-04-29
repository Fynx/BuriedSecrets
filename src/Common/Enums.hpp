/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <type_traits>

#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtCore/QString>


namespace BS {
	enum GameState : quint8 {
		Lost,
		Running,
		Won,
	};


	enum class Type : quint8 {
		Invalid,
		Item,
		Environment,
		Equipment,
		Faction,
		Journal,
		JournalEntry,
		Location,
		Quest,
		Unit,
	};

	QString changeTypeToString(BS::Type type);
	BS::Type changeStringToType(const QString &string);

	// FIXME(Tommalla): Yes, you'll hate me for this, but I couldn't force QHash to hash State. I'm happy to talk
	// about why and try to solve it together with someone.
	// For now it's just going to be a standard enum, because I'm stuck here and don't want it to stay that way.
	enum State {
		Attack = 0,        // Unit
		Assemble,      // Unit
		Heal,          // Unit
		Idle,
		Inside,        // Unit
		Run,           // Unit
		RunAttack,     // Unit
		RunBase,       // Unit
		IdleBase,      // Unit
		Delay,         // Weapon
		Shoot,         // Weapon
		Inactive,      // Quest
		Success,       // Quest
		Fail,          // Quest
		Active,        // Quest
	};

	State changeStringToState(const QString &str);
	QString changeStateToString(BS::State state);

	enum class Attitude : quint8 {
		Aggressive,
		Guard,
		BuildingAggressive,
		BuildingDefensive
	};

	enum class Command : quint8 {
		None,  //Srsly, this should be first
		Assemble,
		Attack,
		Disassemble,
		Enter,
		Heal,
		Leave,
		Move,
		Base
	};

	enum Slot {
		Armor,
		Invalid,
		Fortification,
		Medicament,
		Perception,
		Tool,
		Weapon,
	};

	QString changeSlotToString(BS::Slot slot);
	BS::Slot changeStringToSlot(const QString &string);
	const QList<BS::Slot> getSlots();

	enum class ItemType : quint8 {
		Invalid = 0,

		// Weapons
		AssaultRifle,
		DualPistols,
		Melee,
		Pistol,
		Shotgun,
		SniperRifle,

		// Armor
		Armor,
		Fortification,
		Junk,
		Perception,
		Tool,
		Medicament,
	};

	inline uint qHash(const ItemType &itemType)
	{
		return static_cast<quint8>(itemType);
	}

	// The set of the item types that are weapons.
	const static QSet<ItemType> WeaponTypes {
		ItemType::Invalid,
		ItemType::AssaultRifle,
		ItemType::DualPistols,
		ItemType::Melee,
		ItemType::Pistol,
		ItemType::Shotgun,
		ItemType::SniperRifle
	};

	QString changeItemTypeToString(BS::ItemType type);
	BS::ItemType changeStringToItemType(const QString &str);

	BS::Slot getCorrespondingSlot(BS::ItemType type);


	enum class EntryType : quint8 {
		Death,
		Help,
		Invalid,
		ItemFound,
		Quest,
		Psycho,
	};

	inline uint qHash(const EntryType &entry)
	{
		return static_cast<quint8>(entry);
	}

	QString changeEntryTypeToString(BS::EntryType type);
	BS::EntryType changeStringToEntryType(const QString &str);


	enum class ConditionType : quint8 {
		Invalid,
		QuestFail,
		QuestSuccess,
		FoodCount,
		TimeCount,
		FragsCount,
		ItemFound,
		UnitMet,
		ObjectVisible,
		LocationReached
	};

	inline uint qHash(const ConditionType &cond)
	{
		return static_cast<quint8>(cond);
	}

	QString changeConditionTypeToString(BS::ConditionType type);
	BS::ConditionType changeStringToConditionType(const QString &str);


	namespace Graphic {
		// This is an enum for a reason (underlying value implicitly converted to a numeric type).
		enum Direction {
			Right     = 0,
			RightUp   = 1,
			Up        = 2,
			LeftUp    = 3,
			Left      = 4,
			LeftDown  = 5,
			Down      = 6,
			RightDown = 7,
			Invalid   = 8
		};

		// Ditto.
		// Change ids here to change the order in which the effects are drawn on the screen.
		// Please bear in mind that pre and post effects are stored and sorted separately.
		enum EffectOrder {
			BasePolygon = 255,
			Selection = 1,
			Antipsychosis = 0,
			UnitShadow = 253,
			ShowPath = 254
		};
	}
}
