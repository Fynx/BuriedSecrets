/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QHash>

#include "Graphics/GraphicalEntity.hpp"
#include "Graphics/GraphicsDataManager.hpp"


class GraphicalEntityFactory {
public:
	GraphicalEntityFactory(GraphicsDataManager *graphicsDataManager);
	~GraphicalEntityFactory();
	GraphicalEntity *get(Object *object);
	GraphicalEntity *get(const Object *object);
	/**
	 * @brief Deletes all the allocated objects along with mapping.
	 */
	void deleteObjects();

private:
	GraphicalEntityFactory(const GraphicalEntityFactory &) = delete;

	QHash <const Object *, GraphicalEntity *> map;
	GraphicsDataManager *graphicsDataManager;
};