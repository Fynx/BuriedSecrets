#include "SoundsManager/SoundsManager.hpp"

//TODO replace with DebugManager, don't use qDebug
#include <QtCore>

SoundsManager::SoundsManager()
{
}

void SoundsManager::onEvent(const Event &event)
{
	qDebug() << "<explosion>";
	qDebug() << "event:" << event.toString();
}