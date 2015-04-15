/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorNearCamp.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Common/Strings.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Faction.hpp"
#include "Mind/Mind.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"

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
		if (!mind->getFactionById(unit->getFactionId()))
			continue;

		unit->property(TempData::NearCamp) = false;
		Faction *faction = mind->getFactionById(unit->getFactionId());
		if (!faction)
			continue;
		Location *camp = dynamic_cast<Location *>(mind->getObjectFromUid(faction->getCampUid()));
		if (!camp)
			continue;
		QPointF campPos = mind->physicsEngine()->getPosition(camp);
		if (campPos.isNull()){
			warn("Camp exists but doesn't have any position... wtf?");
			continue;
		}

		QPointF unitPos;
		if (unit->getState() != State::Inside)
			unitPos = mind->physicsEngine()->getPosition(unit);
		else
			unitPos = mind->physicsEngine()->getPosition(unit->getLocation());

		if (QVector2D(unitPos - campPos).length() > faction->getCampRange())
			continue;

		unit->property(TempData::NearCamp) = true;
	}
}
