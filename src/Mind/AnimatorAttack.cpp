/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/AnimatorAttack.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorAttack::AnimatorAttack(Mind *mind) : Animator(mind)
{
	info("Animator Attack created.");
}


void AnimatorAttack::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getCommand() != Command::Attack)
			continue;
		Item *weapon = unit->getUsedItem();
		if (!weapon)
			continue;
		if (weapon->getState() != State::Idle)
			continue;

		Unit *target = dynamic_cast<Unit *>(mind->getObjectFromUid(unit->getTargetObject()));
		if (!target){
			err("Invalid target in attack animator");
			continue;
		}

		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to = mind->physicsEngine()->getPosition(target);
		if (to.isNull() || from.isNull())
			continue;
		float dist = QVector2D(to-from).length();
		if (dist > weapon->getPrototype()->getProperty(Properties::Range).toFloat())
			continue;


		// Ok, letz attack!
		if (dist < weapon->getPrototype()->getProperty(Properties::OptimalRange).toFloat()){
			unit->setState(State::Attack);
			unit->setCurrentPath(QList<QPointF>());
		}
		else{
			if (unit->getState() != State::RunAttack)
				unit->setState(State::RunAttack);
		}
		weapon->setState(State::Shoot);

		// Second argument should be modified depending on units attack skill
		QVector2D direction = QVector2D(to - from);

		// UUUGGGLYYY
		Object *hit = mind->physicsEngine()->getFirstHit(from, direction, weapon->getPrototype()->getProperty(Properties::Range).toFloat());
		info("Object hit: " + hit->getName());
		if (!hit){
			info("Miss!");
			continue;
		}

		// UUUGGGLYYY
		hit->property(TempData::Damage).setValue(weapon->getPrototype()->getProperty(Properties::Damage).toInt() + hit->property(TempData::Damage).toInt());

	}
}

