/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/AnimatorRegenerate.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Faction.hpp"
#include "Mind.hpp"

using namespace BS;


AnimatorRegenerate::AnimatorRegenerate(Mind *mind) : Animator(mind)
{
	info("AnimatorRegenerate created.");
}


void AnimatorRegenerate::act()
{
	for (Object * obj : objects){
		Faction *fac = dynamic_cast<Faction *>(obj);
		if (!fac)
			continue;
		if (!fac->getCamp())
			continue;
		QPointF campPos = mind->physicsEngine()->getPosition(fac->getCamp());
		if (campPos.isNull())
			continue;

		for (int id : fac->getUnits()) {
			Unit *unit = dynamic_cast<Unit *>(mind->getObjectFromUid(id));
			QPointF unitPos;

			if (!unit)
				continue;
			unitPos = mind->physicsEngine()->getPosition(unit);
			if (unitPos.isNull())
				continue;

			if (QVector2D(unitPos - campPos).length() < fac->getCamp()->getRange()){
				unit->setPsychosis(unit->getPsychosis() + unit->getRegeneration());
				unit->setHP(unit->getHP() + unit->getRegeneration());
			}
		}
	}
}
