/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorAttack.hpp"

#include "Common/Strings.hpp"
#include "Common/Geometry.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "Mind/PointToPointEffectData.hpp"

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

		if (unit->getState() == State::Inside)
			unit->setAttitude(Attitude::BuildingAggressive);
		Item *weapon = unit->getUsedItem();
		if (!weapon){
			unit->setCommand(Command::None);
			continue;
		}

		Object *target = dynamic_cast<Object *>(mind->getObjectFromUid(unit->getTargetObject()));
		if (!target){
			unit->setCommand(Command::None);
			warn("Invalid target in attack animator");
			continue;
		}
		if (mind->getFactionById(unit->getFactionId())->isFriendly(target)){
			unit->setCommand(Command::None);
			continue;
		}

		QPointF from = mind->physicsEngine()->getPosition(unit);
		if (unit->getState() == State::Inside)
			from = mind->physicsEngine()->getPosition(unit->getLocation());

		QPointF to = mind->physicsEngine()->getPosition(target);
		if (to.isNull() || from.isNull()){
			err("Invalid points in attack animator");
			unit->setCommand(Command::None);
			continue;
		}
		float dist = QVector2D(to - from).length();
		if (dist > weapon->getPrototype()->getProperty(Properties::Range).toFloat())
			continue;

		// We are close!
		if (dist < weapon->getPrototype()->getProperty(Properties::OptimalRange).toFloat() &&
				unit->getState() != State::Inside){
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
		QPointF hitPoint(0, 0);
		float angle = Geometry::vecToAngle(direction);
		int disp = weapon->getPrototype()->getProperty(Properties::Dispersion).toInt();

		angle += (qrand() % disp) - (disp / 2);
		direction = Geometry::angleToVec(angle);

		// Simulate shot
		Object *hit = mind->physicsEngine()->getFirstHit(from, direction,
				weapon->getPrototype()->getProperty(Properties::Range).toFloat());

		if (!hit){
			info("Miss!");
			hitPoint = from + (direction *
					weapon->getPrototype()->getProperty(Properties::Range).toFloat()).toPointF();
		}
		else{
			info("Object hit: " + hit->getName());
			hit->property(TempData::Damage).setValue(
					weapon->getPrototype()->getProperty(Properties::Damage).toInt() +
					hit->property(TempData::Damage).toInt());
			float hitDist = QVector2D(mind->physicsEngine()->getPosition(hit) - from).length();
			hitPoint = from + (hitDist * direction.normalized()).toPointF();
		}
		if (unit->getState() != State::Inside)
			mind->addEffect(Effect(Effects::Shot,
				new PointToPointEffectData(mind->physicsEngine()->getPosition(unit), hitPoint), 600));
	}
}

