/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QHash>

#include "Graphics/GraphicalObject.hpp"


class GraphicalObjectFactory {
public:
	GraphicalObjectFactory();
	~GraphicalObjectFactory();
	GraphicalObject *get(Object *object);
	GraphicalObject *get(const Object *object);
	/**
	 * @brief Deletes all the allocated objects along with mapping.
	 */
	void deleteObjects();

private:
	GraphicalObjectFactory(const GraphicalObjectFactory &) = delete;

	QHash <const Object *, GraphicalObject *> map;
};