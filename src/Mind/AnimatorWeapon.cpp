/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/AnimatorWeapon.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Item.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorWeapon::AnimatorWeapon(Mind *mind) : Animator(mind)
{
	info("Animator Weapon created.");
}


void AnimatorWeapon::act()
{
	for (Object * obj : objects){
		Item *weapon = dynamic_cast<Item *>(obj);
		if (!weapon)
			continue;
		if (weapon->getUseDelay() > 0){
			weapon->setUseDelay(weapon->getUseDelay() - 1);
			continue;
		}
		if (weapon->getState() == BS::State::Shoot){
			weapon->setUsesLeft(weapon->getUsesLeft() - 1);
			weapon->setUseDelay(weapon->getPrototype()->getProperty(Properties::ShotsInterval).toInt());
		}
		if (weapon->getUsesLeft() == 0){
			weapon->setUsesLeft(weapon->getPrototype()->getProperty(Properties::MagazineSize).toInt());
			weapon->setUseDelay(weapon->getPrototype()->getProperty(Properties::ReloadTime).toInt());
		}
		if (weapon->getUseDelay() > 0)
			weapon->setState(BS::State::Delay);
		else
			weapon->setState(BS::State::Idle);
	}
}

