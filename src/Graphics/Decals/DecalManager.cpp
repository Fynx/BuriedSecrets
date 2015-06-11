/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Decals/DecalManager.hpp"

#include <SFML/Graphics.hpp>

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "Mind/Effect.hpp"
#include "Graphics/Decals/BloodDecal.hpp"
#include "Graphics/GraphicsDataManager.hpp"


DecalManager::DecalManager(const MapManager *mapManager, sf::RenderTexture *mapTexture,
			   GraphicsDataManager *graphicsDataManager, const Viewport *viewport)
		: mapManager{mapManager}, mapTexture{mapTexture}, graphicsDataManager{graphicsDataManager},
		viewport{viewport}
{}


DecalManager::~DecalManager()
{
	qDeleteAll(decals);
}


void DecalManager::drawDecal(const Effect &effect)
{
	// Get the RenderTexture for the surface (get texture bounds from the right decal).
	// WARNING Only map supported now.
	Decal *decal = getDecal(effect.getName());
	decal->draw(*mapTexture, effect.getEffectData());
}


bool DecalManager::isDecal(const Effect &effect) const
{
	return effect.getName() == Decals::UnitHit;
}


Decal *DecalManager::getDecal(const QString &decalName)
{
	auto it = decals.find(decalName);
	if (it != decals.end()) {
		return it.value();
	}

	Decal *decal = nullptr;
	if (decalName == Decals::UnitHit) {
		decal = new BloodDecal{viewport, graphicsDataManager->getTextureSet(Resources::BloodTextureSet)};
	}

	assert(decal != nullptr);
	decals.insert(decalName, decal);
	return decal;
}

