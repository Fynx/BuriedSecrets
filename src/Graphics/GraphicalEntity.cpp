/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicalEntity.hpp"


GraphicalEntity::GraphicalEntity(const Object *object, QList<QPointF> basePolygon)
	: object{object}, basePolygon{basePolygon}
{
	baseCentre = QPointF{0, 0};
	for (const QPointF &p: basePolygon) {
		baseCentre += p;
	}

	baseCentre /= basePolygon.size();
}


GraphicalEntity::~GraphicalEntity()
{}


const Object *GraphicalEntity::getObject() const
{
	return object;
}

