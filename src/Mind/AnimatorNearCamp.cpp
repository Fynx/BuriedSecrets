/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/AnimatorNearCamp.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Common/Strings.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Faction.hpp"
#include "Mind.hpp"

using namespace BS;

AnimatorNearCamp::AnimatorNearCamp(Mind *mind) : Animator(mind)
{
	info("AnimatorNearCamp created.");
}

void AnimatorNearCamp::act()
{
	for (Object * obj : objects) {
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;

		unit->property(TempData::NearCamp) = false;
		Faction *faction = mind->getFactionById(unit->getFactionId());
		if (!faction)
			continue;
		if (!faction->getCamp())
			continue;
		QPointF campPos = mind->physicsEngine()->getPosition(faction->getCamp());
		if (campPos.isNull()){
			warn("Camp exists but doesn't have any position... wtf?");
			continue;
		}

		QPointF unitPos;
		if (unit->getState() != State::Inside)
			unitPos = mind->physicsEngine()->getPosition(unit);
		else
			unitPos = mind->physicsEngine()->getPosition(unit->getLocation());

		if (QVector2D(unitPos - campPos).length() > faction->getCamp()->getRange())
			continue;

		unit->property(TempData::NearCamp) = true;
	}
}
