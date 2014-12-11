/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Quest.hpp"

Quest::Quest(const Prototype *prototype)
	: Object(prototype)
{}

QString Quest::getDescription() const
{
	return prototype->getProperty("description").toString();
}
