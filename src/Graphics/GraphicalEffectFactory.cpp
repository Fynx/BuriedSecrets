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
{}


GraphicalEffect *GraphicalEffectFactory::get(const Effect &effect)
{
	if (effect.getName() == Effects::Selection) {
		return new SelectionEffect{viewport};
	} else if (effect.getName() == Effects::BasePolygon) {
		return new BasePolygonEffect{viewport};
	}

	err("GraphicalEffectFactory: Cannot produce an effect for: " + effect.getName());
	return nullptr;
}


bool GraphicalEffectFactory::isPreEffect(const Effect &effect) const
{
	if (effect.getName() == Effects::Selection) {
		return true;
	} else if (effect.getName() == Effects::BasePolygon) {
		return false;
	}

	return false;
}


