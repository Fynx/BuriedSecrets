/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Event.hpp"

Event::Event(const QString &name)
	: name(name)
{
}

QString Event::toString() const
{
	return name;
}
