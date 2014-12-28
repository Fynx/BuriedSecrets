/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorDie.hpp"

//TODO use DebugManager instead
#include <QtCore>

#include "Mind/Mind.hpp"
#include "GameObjects/Unit.hpp"

AnimatorDie::AnimatorDie(Mind *mind) : Animator(mind)
{
	qDebug() << "AnimatorDie created.";
}


void AnimatorDie::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getHP() <= 0){
			qDebug() << "Unit dies. Id: " <<unit->getUid();
			mind->removeObject(unit);
		}
	}
}
