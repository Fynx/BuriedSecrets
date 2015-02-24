/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/AnimatorAttack.hpp"

#include "Common/Strings.hpp"
#include "Common/Geometry.hpp"
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
		if (unit->getCommand() != Command::Attack){
			if (unit->getState() == State::Attack || unit->getState() == State::RunAttack)
				unit->setState(State::Idle);
			continue;
		}
		Item *weapon = unit->getUsedItem();
		if (!weapon)
			continue;


		Unit *target = dynamic_cast<Unit *>(mind->getObjectFromUid(unit->getTargetObject()));
		if (!target){
			err("Invalid target in attack animator");
			continue;
		}

		QPointF from = mind->physicsEngine()->getPosition(unit);
		if (from.isNull() && unit->getState() == State::Inside)
			from = mind->physicsEngine()->getPosition((Object *)unit->getLocation());

		QPointF to = mind->physicsEngine()->getPosition(target);
		if (to.isNull() || from.isNull()){
			err("Invalid points in attack animator");
			continue;
		}
		float dist = QVector2D(to-from).length();
		if (dist > weapon->getPrototype()->getProperty(Properties::Range).toFloat())
			continue;

		// We are close!
		if (dist < weapon->getPrototype()->getProperty(Properties::OptimalRange).toFloat() && unit->getState() != State::Inside){
			unit->setCurrentPath(QList<QPointF>());
			if (weapon->getState() != State::Idle)
				continue;
			unit->setState(State::Attack);
		}
		else{
			if (weapon->getState() != State::Idle)
				continue;
			if (unit->getState() != State::RunAttack && unit->getState() != State::Inside)
				unit->setState(State::RunAttack);
		}

		info(unit->getName() + " is attacking! Distance: " + QString::number(dist));
		weapon->setState(State::Shoot);

		// Calculate direction...
		QVector2D direction = QVector2D(to - from);
		float angle = Geometry::vecToAngle(direction);
		int disp = weapon->getPrototype()->getProperty(Properties::Dispersion).toInt();
		angle += (qrand() % disp) - (disp / 2);
		unit->property(TempData::ShotAngle) = angle;
		direction = Geometry::angleToVec(angle);
		//info("Angle: " + QString::number(angle) + " dir " + QString::number(direction.x()) + " " + QString::number(direction.y()));

		// Simulate shot
		Object *hit = mind->physicsEngine()->getFirstHit(from, direction, weapon->getPrototype()->getProperty(Properties::Range).toFloat());
		if (!hit){
			info("Miss!");
			continue;
		}
		info("Object hit: " + hit->getName());

		hit->property(TempData::Damage).setValue(weapon->getPrototype()->getProperty(Properties::Damage).toInt() + hit->property(TempData::Damage).toInt());
	}
}

