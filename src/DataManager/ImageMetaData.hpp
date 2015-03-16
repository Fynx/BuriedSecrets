/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Common/Enums.hpp"


struct ImageMetaData {
	// TODO ctor

	int frame;
	BS::Graphic::Direction direction;
	BS::State state;
	// TODO LocationState
	// TODO Weapon state plax!
	BS::ItemType weapon;
};