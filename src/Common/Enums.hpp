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
		Building,
		Camp,
		Equipment,
		Faction,
		Fortification,
		Journal,
		Unit,
	};

	QString changeTypeToString(BS::Type type);
	BS::Type changeStringToType(const QString &string);

	// FIXME(Tommalla): Yes, you'll hate me for this, but I couldn't force QHash to hash State. I'm happy to talk
	// about why and try to solve it together with someone.
	// For now it's just going to be a standard enum, because I'm stuck here and don't want it to stay that way.
	enum State {
		Idle,
		Attack,        // Unit
		RunAttack,     // Unit
		Run,           // Unit
		Heal,          // Unit
		Inside,        // Unit
		Shoot,         // Weapon
		Delay          // Weapon
	};

	enum class Command : quint8 {
		None,  //Srsly, this should be first
		Attack,
		Construct,
		Deconstruct,
		EnterBuilding,
		EnterFortification,
		Heal,
		LeaveBuilding,
		Move
	};

	enum Slot {
		Invalid,
		Weapon,
		Tool,
		Medicament,
		Armor,
		Fortification,
		Perception
	};

	QString changeSlotToString(BS::Slot slot);
	BS::Slot changeStringToSlot(const QString &string);
	const QList<BS::Slot> getSlots();

	enum class ItemType : quint8 {
		Storyline,
		Material,
		Personal,
		Fortification,
	};

	State changeStringToState(const QString &str);
	QString changeStateToString(BS::State state);

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
