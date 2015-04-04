/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QString>

#include "Mind/Effect.hpp"
#include "Graphics/Effects/GraphicalEffect.hpp"
#include "UserInterface/Viewport/Viewport.hpp"


/**
 * @brief A factory that can return graphical effects.
 */
class GraphicalEffectFactory {
public:
	GraphicalEffectFactory(const Viewport *viewport);

	GraphicalEffect *get(const Effect& effect);
	// TODO: If needed, this class can implement a pool of effects to avoid doing a lot of allocations.

	/**
	 * @brief True if an effect is a PreEffect.
	 */
	bool isPreEffect(const Effect& effect) const;

private:
	QSet<QString> preEffects;
	const Viewport *viewport;
};