/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorResult.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorResult::AnimatorResult(Mind *mind) : Animator(mind)
{
	info("Animator Result created.");
}


void AnimatorResult::act()
{
	for (Object * obj : objects){
		Location *loc = dynamic_cast<Location *>(obj);
		if (!loc)
			continue;

		if (loc->getUnitsUids().size() > 0){
			mind->setGameState(GameState::Won);
			return;
		}
	}
	if (mind->getPlayerFaction()->getUnitsUids().size() == 0)
		mind->setGameState(GameState::Lost);
}
