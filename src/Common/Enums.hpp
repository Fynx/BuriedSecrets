/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

namespace BS {
	enum class Type : quint8 {
		Invalid,
		Building,
		Equipment,
		Fortification,
		Journal,
		Unit,
		Mob,
	};

	enum class State : quint8 {
		Idle,
		Run,
		Shoot,
	};

	enum class ItemType : quint8 {
		Storyline,
		Material,
		Personal,
		Fortification,
	};
}