/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "GameObjects/Camp.hpp"

Camp::Camp(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Camp::getType() const
{
	return BS::Type::Camp;
}

qreal Camp::getRange() const
{
	return prototype->getProperty("range").toDouble();
}
