/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicalEffectFactory.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "Graphics/BasePolygonEffect.hpp"
#include "Graphics/SelectionEffect.hpp"
#include "Mind/SelectionEffectData.hpp"


GraphicalEffectFactory::GraphicalEffectFactory(const Viewport *viewport)
	: viewport{viewport}
{}


GraphicalEffect *GraphicalEffectFactory::get(const Effect &effect)
{
	if (effect.getName() == Effects::Selection) {
		const SelectionEffectData *sdata = dynamic_cast<const SelectionEffectData *>(effect.getEffectData());
		if (sdata == nullptr) {
			err("GraphicalEffectFactory: Got data for SelectionEffect, but data pointer doesn't cast to "
					"SelectionEffectData. Skipping.");
			return nullptr;
		}
		QColor color = sdata->getColor();
		return new SelectionEffect{viewport,
				sf::Color{(sf::Uint8)color.red(), (sf::Uint8)color.green(), (sf::Uint8)color.blue(),
					  (sf::Uint8)color.alpha()}};
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


