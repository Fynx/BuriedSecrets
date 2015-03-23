/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimationAnimator.hpp"

#include "DataManager/TextureSetData.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"


AnimationAnimator::AnimationAnimator(Mind *mind)
	: Animator{mind}
{
	info("AnimationAnimator created.");
}


void AnimationAnimator::act()
{
	for (auto &obj: objects) {
		if (obj->getState() == BS::State::Inside)
			continue;
		BS::State state = obj->getState();
		BS::ItemType weapon = BS::ItemType::Invalid;
		const Unit *unit = dynamic_cast<const Unit *>(obj);
		if (unit != nullptr) {
			Item *item = unit->getUsedItem();
			if (item != nullptr) {
				const auto &types = item->getItemTypes();
				for (const auto &type: types) {
					if (BS::WeaponTypes.contains(type)) {
						weapon = type;
						break;
					}
				}
			}
		}

		int allFrames = obj->getPrototype()->getTextureSetData()->getFramesNumber(state, weapon);
		int currentFrame = obj->getFrame();
		if (currentFrame + 1 >= allFrames) {
			obj->setState(BS::State::Idle);
			obj->setFrame(0);
		} else {
			obj->setFrame(currentFrame + 1);
		}
	}
}
