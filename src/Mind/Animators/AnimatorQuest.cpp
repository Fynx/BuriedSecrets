/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorQuest.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Common/Strings.hpp"
#include "GameObjects/Quest.hpp"
#include "GameObjects/Faction.hpp"
#include "GameObjects/Journal.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorQuest::AnimatorQuest(Mind *mind) : Animator(mind)
{
	info("Animator Quest created.");
}


void AnimatorQuest::act()
{
	for (Object *obj : objects) {
		Faction *fac = dynamic_cast<Faction *>(obj);
		if (!fac)
			continue;

		for (int id : fac->getQuests()){
			Quest *quest = mind->getQuest(id);
			if (!quest)
				continue;

			switch (quest->getState()) {
			case State::Inactive:
				if (Quest::evaluateConditions(quest->getStartConds(), mind, fac->getFactionId())) {

					quest->setState(State::Active);
					JournalEntry *entry = mind->getJournalEntry(quest->getStartEntry());
					if (entry)
						fac->getJournal()->addEntry(entry);
				}

				break;
			case State::Active:
				if (Quest::evaluateConditions(quest->getSuccessConds(), mind, fac->getFactionId())) {
					quest->setState(State::Success);
					JournalEntry *entry = mind->getJournalEntry(quest->getSuccessEntry());
					if (entry)
						fac->getJournal()->addEntry(entry);
					if (quest->isFinal())
						mind->setGameState(GameState::Won);
				} else if (Quest::evaluateConditions(quest->getFailConds(), mind, fac->getFactionId())) {
					quest->setState(State::Fail);
					JournalEntry *entry = mind->getJournalEntry(quest->getFailEntry());
					if (entry)
						fac->getJournal()->addEntry(entry);
				}
				break;
			case State::Fail:
				break;
			case State::Success:
				break;
			default:
				break;
			}
		}
	}
}
