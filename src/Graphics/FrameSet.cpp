/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/FrameSet.hpp"


FrameSet::~FrameSet()
{
	auto vals = values();
	for (sf::Texture *val : vals) {
		delete val;
	}
}
