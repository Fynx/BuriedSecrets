/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Enums.hpp"

namespace BS {

	State getStateFromString(const QString &str)
	{
		BS::State result = BS::State::Idle;
		if (str == "Run") {
			result = BS::State::Run;
		} else if (str == "Shooting") {
			result = BS::State::Shoot;
		}

		return result;
	}

}