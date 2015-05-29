/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Effect.hpp"

#include <QDebug>


Effect::Effect(const QString &name, EffectData *effectData, int timeout)
	: name{name}, effectData{effectData}, timeout{timeout}
{}


Effect::Effect(const QString &name, EffectData *effectData)
	: name{name}, effectData{effectData}, timeout{-1}
{}


QString Effect::getName() const
{
	return name;
}


const EffectData *Effect::getEffectData() const
{
	return effectData;
}


int Effect::getTimeout() const
{
	return timeout;
}


bool Effect::isInfinite() const
{
	return timeout < 0;
}


void Effect::setTimeout(const int timeout)
{
	this->timeout = timeout;
}


void Effect::destroyData()
{
	delete effectData;
}
