/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/Prototype.hpp"


bool Prototype::hasProperty(const QString &key) const
{
	return properties.contains(key);
}


QVariant Prototype::getProperty(const QString &key) const
{
	if (properties.contains(key))
		return properties[key];
	else {
		qDebug() << "Notice: the prototype doesn't have \"" << key <<"\"";
		return QVariant(0);
	}
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


void Prototype::addAnimationData(BS::State state, const AnimationData *data)
{
	qDebug() << "Adding animationData for " << data->getName() << "(" << BS::changeStateToString(state) << ")";
	Q_ASSERT(!animationData.contains(state));
	animationData[state] = data;
}


const QPointF Prototype::getBaseCentre() const
{
	return baseCentre;
}


const QList< QPointF > Prototype::getBasePolygon() const
{
	return basePolygon;
}


void Prototype::setBaseCentre(const QPointF &baseCentre)
{
	this->baseCentre = baseCentre;
}


void Prototype::setBasePolygon(const QList< QPointF > &basePolygon)
{
	this->basePolygon = basePolygon;
}
