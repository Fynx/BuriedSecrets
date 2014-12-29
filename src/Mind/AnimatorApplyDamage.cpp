/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorApplyDamage.hpp"

//TODO use DebugManager instead
#include <QtCore>

#include "Mind/Mind.hpp"
#include "GameObjects/Unit.hpp"

AnimatorApplyDamage::AnimatorApplyDamage(Mind *mind) : Animator(mind)
{
	qDebug() << "AnimatorApplyDamage created.";
}


void AnimatorApplyDamage::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		float damage = unit->property("Damage").toFloat();
		unit->property("Damage").fromValue(0.0);
		damage = damage * (1.0 - unit->getDamageControl());
		unit->setHP(unit->getHP() - damage);
	}
}
