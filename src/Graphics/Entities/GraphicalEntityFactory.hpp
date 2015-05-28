/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QHash>

#include "Graphics/Effects/GraphicalEffectFactory.hpp"
#include "Graphics/Entities/EffectGraphicalEntity.hpp"
#include "Graphics/Entities/GraphicalEntity.hpp"

class GraphicsDataManager;
class Viewport;


/**
 * @brief Factory for the GraphicalEntities.
 */
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
	 * @brief
	 *
	 * @param effectData ...
	 * @return GraphicalEntity*
	 */
	EffectGraphicalEntity *getOrCreateEffectEntity(const Effect &effect);
	/**
	 * @brief Deletes all the allocated objects along with mapping.
	 */
	void deleteObjects();

private:
	GraphicalEntityFactory(const GraphicalEntityFactory &) = delete;

	GraphicalEffectFactory graphicalEffectFactory;

	QHash <const Object *, GraphicalEntity *> objectEntities;
	QHash <const EffectData *, EffectGraphicalEntity *> effectEntities;
	GraphicsDataManager *graphicsDataManager;
	const Viewport *viewport;;
};
