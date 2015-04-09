/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/Prototype.hpp"

#include <cassert>

#include "DataManager/TextureSetData.hpp"


Prototype::Prototype()
	: textureSetData(nullptr)
{}


Prototype::~Prototype()
{
	delete textureSetData;
}


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


const TextureSetData *Prototype::getTextureSetData() const
{
	return textureSetData;
}


void Prototype::setTextureSetData(TextureSetData *textureSetData)
{
	delete this->textureSetData;
	this->textureSetData = textureSetData;
}


const QPointF Prototype::getBaseCentre() const
{
	return baseCentre;
}


const QList<QPointF> Prototype::getBasePolygon() const
{
	return basePolygon;
}


void Prototype::setBaseCentre(const QPointF &baseCentre)
{
	this->baseCentre = baseCentre;
}


void Prototype::setBasePolygon(const QList<QPointF> &basePolygon)
{
	this->basePolygon = basePolygon;
}
