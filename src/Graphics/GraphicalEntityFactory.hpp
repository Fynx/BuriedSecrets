/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QHash>

#include "Graphics/GraphicalEffectFactory.hpp"
#include "Graphics/GraphicalEntity.hpp"
#include "Graphics/GraphicsDataManager.hpp"
#include "UserInterface/Viewport.hpp"


class GraphicalEntityFactory {
public:
	GraphicalEntityFactory(GraphicsDataManager *graphicsDataManager, const Viewport *viewport);
	~GraphicalEntityFactory();

	/**
	 * @brief Tries to return the entity for the object, if it was ever created.
	 * Nullptr on failure.
	 */
	GraphicalEntity *get(Object *object) const;
	/**
	 * @brief Tries to return the entity for the object, if it was ever created.
	 * Nullptr on failure.
	 */
	GraphicalEntity *get(const Object *object) const;
	/**
	 * @brief Returns an object (creates it if it did not exist before).
	 */
	GraphicalEntity *getOrCreate(Object *object);
	/**
	 * @brief Returns an object (creates it if it did not exist before).
	 */
	GraphicalEntity *getOrCreate(const Object *object);
	/**
	 * @brief Deletes all the allocated objects along with mapping.
	 */
	void deleteObjects();

private:
	GraphicalEntityFactory(const GraphicalEntityFactory &) = delete;

	GraphicalEffectFactory graphicalEffectFactory;

	QHash <const Object *, GraphicalEntity *> map;
	GraphicsDataManager *graphicsDataManager;
	const Viewport *viewport;;
};