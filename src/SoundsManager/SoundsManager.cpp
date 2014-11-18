#include "SoundsManager/SoundsManager.h"

//TODO replace with DebugManager, don't use qDebug
#include <QtCore>

SoundsManager::SoundsManager()
{
}

void SoundsManager::onEvent()
{
	qDebug() << "<explosion>";
}