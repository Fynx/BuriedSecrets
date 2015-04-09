/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorAssemble.hpp"

#include "Common/Enums.hpp"
#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "Mind/ObjectRadiusEffectData.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"

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
		if (!ikeaSet && (unit->getState() != State::RunBase && unit->getState() != State::IdleBase)){
			unit->setCommand(Command::None);
			continue;
		}

		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to = unit->getTargetPoint();

		if (to.isNull() || from.isNull())
			continue;
		if (QVector2D(to-from).length() > epsilon)
			continue;

		QString spawned;
		if (unit->getState() == State::RunBase || unit->getState() == State::IdleBase)
			spawned = "Player Camp";
		else if (ikeaSet) {
			if (ikeaSet->getPrototype()->hasProperty(Properties::SpawnedType))
				spawned = ikeaSet->getPrototype()->getProperty(Properties::SpawnedType).toString();
			unit->getEquipment()->removeItem(ikeaSet);
		}

		Object *fort = mind->createDefaultObject(BS::Type::Location, spawned);
		mind->addObject(fort, unit->getTargetPoint());
		fort->setFactionId(unit->getFactionId());
		if (spawned == "Player Camp"){
			mind->getFactionById(unit->getFactionId())->setCamp(fort->getUid());;
			mind->addEffect(Effect(Effects::Antipsychosis,
					new ObjectRadiusEffectData(fort,
							mind->getFactionById(unit->getFactionId())->getCampRange())));
		}

		unit->setState(State::Idle);
		unit->setCommand(Command::None);
	}
}
