/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorApplyDamage.hpp"

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
		if (damage == 0)
			continue;
		unit->property(TempData::Damage).setValue(0.0);

		damage = damage * (1.0 - unit->getDamageControl());

		info("ApplyDamage: " + unit->getName() + " " + QString::number(unit->getHP()) + " : " + QString::number(damage));
		unit->setHP(unit->getHP() - damage);
	}
}
