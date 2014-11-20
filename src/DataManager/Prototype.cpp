#include "DataManager/Prototype.hpp"

QVariant Prototype::getProperty(const QString &key) const
{
	return properties[key];
}

void Prototype::setProperty(const QString &key, const QVariant &value)
{
	properties[key] = value;
}

QDataStream &operator<<(QDataStream &out, const Prototype &prototype)
{
	return out;
}

QDataStream &operator>>(QDataStream &in, Prototype &prototype)
{
	return in;
}

