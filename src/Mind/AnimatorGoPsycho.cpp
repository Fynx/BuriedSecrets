/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/AnimatorGoPsycho.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Faction.hpp"
#include "Mind.hpp"

using namespace BS;


AnimatorGoPsycho::AnimatorGoPsycho(Mind *mind) : Animator(mind)
{
	info("AnimatorGoPsycho created.");
}


void AnimatorGoPsycho::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		Faction *fac = mind->getFactionById(unit->getFaction());
		if (!fac->getCamp())
			continue;
		QPointF campPos = mind->physicsEngine()->getPosition(fac->getCamp());
		if (campPos.isNull())
			continue;

		QPointF unitPos;

		unitPos = mind->physicsEngine()->getPosition(unit);
		if (unitPos.isNull())
			continue;

		if (QVector2D(unitPos - camPos).length() > fac->getCamp()->getRange()){
			unit->setPsychosis(unit->getPsychosis()-1);
		}
		if (unit->getPsychosis() == 0){
			//ToDo - Psychosis effect
		}
	}
}
