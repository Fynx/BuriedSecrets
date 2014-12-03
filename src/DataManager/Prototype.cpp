/* YoLoDevelopment, 2014
 * All rights reserved.
 */
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
	out << prototype.properties;

	return out;
}

QDataStream &operator>>(QDataStream &in, Prototype &prototype)
{
	in >> prototype.properties;

	for (auto it = prototype.properties.begin(); it != prototype.properties.end(); ++it)
		qDebug() << "\t\t" << it.key() << it.value();

	return in;
}

