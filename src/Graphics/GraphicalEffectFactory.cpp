/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicalEffectFactory.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "Graphics/BasePolygonEffect.hpp"
#include "Graphics/SelectionEffect.hpp"


GraphicalEffectFactory::GraphicalEffectFactory(const Viewport *viewport)
	: viewport{viewport}
{
	preEffects.insert(Effects::Selection);
	preEffects.insert(Effects::EnterCommand);
	preEffects.insert(Effects::FriendlyCommand);
	preEffects.insert(Effects::HostileCommand);
}


GraphicalEffect *GraphicalEffectFactory::get(const Effect &effect)
{
	QString name = effect.getName();
	if (name == Effects::Selection) {
		return new SelectionEffect{viewport, sf::Color::Cyan};
	} else if (name == Effects::FriendlyCommand) {
		return new SelectionEffect{viewport, sf::Color::Green};
	} else if (name == Effects::HostileCommand) {
		return new SelectionEffect{viewport, sf::Color::Red};
	} else if (name == Effects::EnterCommand) {
		return new SelectionEffect{viewport, sf::Color::Cyan};
	} else if (name == Effects::BasePolygon) {
		return new BasePolygonEffect{viewport};
	}

	err("GraphicalEffectFactory: Cannot produce an effect for: " + effect.getName());
	return nullptr;
}


bool GraphicalEffectFactory::isPreEffect(const Effect &effect) const
{
	return preEffects.contains(effect.getName());
}


