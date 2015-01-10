/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DebugManager/DebugManager.hpp"
#include "SoundsManager/SoundsManager.hpp"

SoundsManager::SoundsManager()
{
}

void SoundsManager::onEvent(const Event &event)
{
	info(QString("SoundManager: event ") + event.toString());
}