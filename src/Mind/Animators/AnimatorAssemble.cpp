/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorAssemble.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "Common/Enums.hpp"
#include "Common/Strings.hpp"

using namespace BS;

AnimatorAssemble::AnimatorAssemble(Mind *mind) : Animator(mind)
{
	info("Animator Construct created.");
}

void AnimatorAssemble::act()
{
	for (Object * obj : objects) {
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getCommand() != Command::Assemble)
			continue;

		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to = unit->getTargetPoint();

		if (to.isNull() || from.isNull())
			continue;
		if (QVector2D(to-from).length() > epsilon)
			continue;

		Item *castoramaSet = unit->getEquipment()->getSlotItem(BS::Slot::Fortification);
		if (castoramaSet){

			if (castoramaSet->getPrototype()->hasProperty(Properties::SpawnedType)){
				QString  spawned = castoramaSet->getPrototype()->getProperty(Properties::SpawnedType).toString();
				Object *fort = mind->createDefaultObject(BS::Type::Location, spawned);
				mind->addObject(fort, unit->getTargetPoint());
				unit->getEquipment()->removeItem(castoramaSet);
			}
		}
		unit->setCommand(Command::None);
	}
}
