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
		Building,
		Camp,
		Equipment,
		Fortification,
		Journal,
		Mob,
		Unit,
	};

	QString changeTypeToString(BS::Type type);
	BS::Type changeStringToType(const QString &string);

	// FIXME(Tommalla): Yes, you'll hate me for this, but I couldn't force QHash to hash State. I'm happy to talk
	// about why and try to solve it together with someone.
	// For now it's just going to be a standard enum, because I'm stuck here and don't want it to stay that way.
	enum State {
		Idle,
		Run,
		Shoot,
	};

	enum class Command : quint8 {
		None,
		Attack,
		Move,
		EnterBuilding,
		EnterFortification,
		Heal,
		Construct,
		Deconstruct
	};

	enum class ItemType : quint8 {
		Storyline,
		Material,
		Personal,
		Fortification,
	};

	State getStateFromString(const QString &str);

	namespace Graphic {
		// This is an enum for a reason (underlying value implicitly converted to a numeric type).
		enum Direction {
			Right = 0,
			RightUp = 1,
			Up = 2,
			LeftUp = 3,
			Left = 4,
			LeftDown = 5,
			Down = 6,
			RightDown = 7
		};
	}
}
