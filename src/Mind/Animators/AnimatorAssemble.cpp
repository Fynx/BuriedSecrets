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
	info("Animator Assemble created.");
}

void AnimatorAssemble::act()
{
	for (Object * obj : objects) {
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getCommand() != Command::Assemble)
			continue;

		Item *ikeaSet = unit->getUsedItem();
		if (!ikeaSet){
			unit->setCommand(Command::None);
			continue;
		}

		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to = unit->getTargetPoint();

		if (to.isNull() || from.isNull())
			continue;
		if (QVector2D(to-from).length() > epsilon)
			continue;

		if (ikeaSet->getPrototype()->hasProperty(Properties::SpawnedType)){
			QString  spawned = ikeaSet->getPrototype()->getProperty(Properties::SpawnedType).toString();
			Object *fort = mind->createDefaultObject(BS::Type::Location, spawned);
			mind->addObject(fort, unit->getTargetPoint());
			unit->getEquipment()->removeItem(ikeaSet);
		}
		else
			warn("Invalid Fortification item");

		unit->setCommand(Command::None);
	}
}
