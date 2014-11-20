#include "SoundsManager/SoundsManager.hpp"

//TODO replace with DebugManager, don't use qDebug
#include <QtCore>

SoundsManager::SoundsManager()
{
}

void SoundsManager::onEvent()
{
	qDebug() << "<explosion>";
}