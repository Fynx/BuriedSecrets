/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/Prototype.hpp"

QVariant Prototype::getProperty(const QString &key) const
{
	if (properties.contains(key))
		return properties[key];
	else
		return QVariant(0);
}

void Prototype::setProperty(const QString &key, const QVariant &value)
{
	properties[key] = value;
}

const QList<const AnimationData *> Prototype::getAnimationsData() const
{
	QList<const AnimationData *> result;
	for (auto val: animationData) {
		result.append(val);
	}
	return result;
}

const AnimationData *Prototype::getAnimationData(const BS::State &state) const
{
	auto it = animationData.find(state);
	Q_ASSERT(it != animationData.end());
	return it.value();
}

void Prototype::addAnimationData(const BS::State &state, const AnimationData *data)
{
	qDebug() << "Adding animationData for " << data->getName();
	Q_ASSERT(!animationData.contains(state));
	animationData[state] = data;
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

