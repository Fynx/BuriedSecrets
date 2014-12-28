/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorMove.hpp"

//TODO use DebugManager instead
#include <QtCore>

#include "Mind/Mind.hpp"
#include "../GameObjects/Unit.hpp"


AnimatorMove::AnimatorMove(Mind *mind) : Animator(mind)
{
	qDebug() << "AnimatorMove created.";
}


void AnimatorMove::act()
{
	for (Object * obj : objects) {
		Unit *unit = dynamic_cast<Unit *>(obj);
		QVector2D dir (0, 0);

		if (!unit)
			continue;

		if ( !(obj->getState() == BS::Idle) && !(obj->getState() == BS::Run))
			continue;

		if (unit->getCurrentPath().size() == 0) {
			if (obj->getState() == BS::Run){
				obj->setState(BS::Idle);
				mind->physicsEngine()->setVelocity(obj, dir * 0);
			}
			continue;
		}

		dir = QVector2D(unit->getCurrentPath().first() - mind->physicsEngine()->getPosition(obj));


		if (dir.length() < epsilon)
			unit->getCurrentPath().removeFirst();
		else {
			if (obj->getState() == BS::Idle)
				obj->setState(BS::Run);
			dir.normalize();
			dir = dir *unit->getSpeed();
			qDebug() << dir.x() << " " << dir.y();
			mind->physicsEngine()->setVelocity(obj, dir);
		}
	}
}
