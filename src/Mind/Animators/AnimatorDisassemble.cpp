/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorDisassemble.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "Common/Enums.hpp"
#include "Common/Strings.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"

using namespace BS;

AnimatorDisassemble::AnimatorDisassemble(Mind *mind) : Animator(mind)
{
	info("Animator Disassemble created.");
}

void AnimatorDisassemble::act()
{
	for (Object * obj : objects) {
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;

		if (unit->getCommand() != Command::Disassemble)
			continue;
		Location *target = mind->getLocation(unit->getTargetObject());
		if (!target){
			unit->setCommand(Command::None);
			continue;
		}

		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to = mind->physicsEngine()->getPosition(target);

		if (to.isNull() || from.isNull())
			continue;
		if (QVector2D(to-from).length() > epsilon)
			continue;

		if (target->getUnitsUids().size() > 0) {
			unit->setCommand(Command::None);
			continue;
		}

		bool isCamp = mind->getFactionById(unit->getFactionId())->getCampUid() == target->getUid();

		if (target->getPrototype()->hasProperty(Properties::SpawnedType)) {
			QString  spawned = target->getPrototype()->getProperty(Properties::SpawnedType).toString();
			Item *item = dynamic_cast<Item *>(mind->createDefaultObject(BS::Type::Item, spawned));
			mind->addObject(item);

			Faction *faction = mind->getFactionById(unit->getFactionId());
			if (faction)
				faction->getEquipment()->addItem(item);

			info("Disassemble. Id: " + QString::number(target->getUid()));
			mind->removeObject(target);
		} else if (isCamp) {
			info("Disassemble. Id: " + QString::number(target->getUid()));
			mind->removeObject(target);
			unit->setState(State::IdleBase);
			unit->setCommand(Command::Base);
		}

		unit->setCommand(Command::None);
	}
}
