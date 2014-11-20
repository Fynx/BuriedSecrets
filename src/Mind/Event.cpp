#include "Mind/Event.hpp"

Event::Event(const QString &name)
	: name(name)
{
}

QString Event::toString() const
{
	return name;
}
