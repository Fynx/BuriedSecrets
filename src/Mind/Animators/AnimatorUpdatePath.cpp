/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorUpdatePath.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/MapManager/MapManager.hpp"
#include "Mind/Mind.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"

using namespace BS;


AnimatorUpdatePath::AnimatorUpdatePath(Mind *mind) : Animator(mind)
{
	timer.restart();
	info("Animator Update Path created.");
}


void AnimatorUpdatePath::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (unit == nullptr) {
			continue;
		}
		Command comm = unit->getCommand();
		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to(0, 0);

		if ((comm == Command::Attack && unit->getState() != State::Attack) || (comm == Command::Heal) ||
				(comm == Command::Disassemble)) {
			to = mind->physicsEngine()->getPosition(mind->getObjectFromUid(unit->getTargetObject()));
		} else if (comm == Command::Enter){
			Location *target = (Location *)mind->getObjectFromUid(unit->getTargetObject());
			if (target == nullptr) {
				unit->setCommand(Command::None);
				unit->setState(State::Idle);
				unit->setCurrentPath(QList<QPointF>());
				continue;
			}

			to = mind->physicsEngine()->getPosition(target) + target->getOffset();
		}

		if ((comm == Command::Assemble) || (comm == Command::Move)) {
			to = unit->getTargetPoint();
		}
		if ((comm == Command::Move) && to.isNull())
			continue;

		if (from.isNull() || to.isNull()) {
			unit->setCurrentPath(QList<QPointF>());
			continue;
		}

		if (comm == Command::Move && QVector2D(from - to).length() < epsilon) {
			if (unit->getState() == State::RunBase || unit->getState() == State::IdleBase)
				unit->setCommand(Command::Base);
			else
				unit->setCommand(Command::None);
			unit->setCurrentPath(QList<QPointF>());
			continue;
		}

		bool calculatePath = false;
		int timestamp = timer.elapsed();
		auto &path = unit->getCurrentPath();

		if (path.empty()) {
			calculatePath = true;
		} else {
			const float dist = BS::Geometry::distance(path.back(), to);
			const float baseRadius = unit->getPrototype()->getProperty(Properties::BaseRadius).toFloat();
			if (timestamp - unit->property(TempData::PreviousPathTimestamp).toInt() >= burnout &&
					dist >= 6.0f * baseRadius) {
				calculatePath = true;
			} else if (unit->getFactionId() == mind->getPlayerFaction()->getFactionId() &&
					dist >= 2.0f * baseRadius) {
				calculatePath = true;
			}
		}

		if (calculatePath) {
			unit->property(TempData::PreviousPathTimestamp) = timestamp;
			unit->setCurrentPath(mind->getMapManager()->getPath(unit, to));
		} else if(isStuck(unit, (10 * from).toPoint())) {
			path.pop_front();
		}
	}
}


bool AnimatorUpdatePath::isStuck(Unit *unit, const QPoint &position)
{
	const QPointF previousPos = unit->property(TempData::PreviousPosition).toPoint();
	unit->property(TempData::PreviousPosition) = position;
	return previousPos == position;
}

