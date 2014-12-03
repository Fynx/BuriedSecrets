/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Event.hpp"

class SoundsManager {
public:
	SoundsManager();

	//TODO event as an arg
	void onEvent(const Event &event);
};