/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <type_traits>

#include <QtCore/QHash>
#include <QtCore/QString>


namespace BS {
	enum class Type : quint8 {
		Invalid,
		Item,
		Equipment,
		Faction,
		Journal,
		Location,
		Unit,
	};

	QString changeTypeToString(BS::Type type);
	BS::Type changeStringToType(const QString &string);

	// FIXME(Tommalla): Yes, you'll hate me for this, but I couldn't force QHash to hash State. I'm happy to talk
	// about why and try to solve it together with someone.
	// For now it's just going to be a standard enum, because I'm stuck here and don't want it to stay that way.
	enum State {
		Attack,        // Unit
		Delay,         // Weapon
		Heal,          // Unit
		Idle,
		Inside,        // Unit
		Run,           // Unit
		RunAttack,     // Unit
		Shoot,         // Weapon
	};

	State changeStringToState(const QString &str);
	QString changeStateToString(BS::State state);

	enum class Attitude : quint8 {
		Aggressive,
		Guard,
		Coward,
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
		Move
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
		Armor,
		Fortification,
		Invalid,
		Junk,
		Perception,
		Tool,
		Medicament,

		// Weapons
		AssaultRifle,
		DualPistols,
		Melee,
		Pistol,
		Shotgun,
		SniperRifle,
	};

	QString changeItemTypeToString(BS::ItemType type);
	BS::ItemType changeStringToItemType(const QString &str);

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
			RightDown = 7
		};

		// Ditto.
		// Change ids here to change the order in which the effects are drawn on the screen.
		// Please bear in mind that pre and post effects are stored and sorted separately.
		enum EffectOrder {
			BasePolygon = 99999999,
			Selection = 0
		};
	}
}
