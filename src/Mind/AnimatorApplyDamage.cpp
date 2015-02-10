/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorApplyDamage.hpp"

#include <QtCore>

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

AnimatorApplyDamage::AnimatorApplyDamage(Mind *mind) : Animator(mind)
{
	info("AnimatorApplyDamage created.");
}


void AnimatorApplyDamage::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		float damage = unit->property(TempData::Damage).toFloat();
		unit->property(TempData::Damage).fromValue(0.0);
		damage = damage * (1.0 - unit->getDamageControl());
		unit->setHP(unit->getHP() - damage);
	}
}
