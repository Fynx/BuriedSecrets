/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Entities/EffectGraphicalEntity.hpp"


EffectGraphicalEntity::EffectGraphicalEntity(const Viewport *viewport)
	: GraphicalEntity{nullptr, QList<QPointF>{}, nullptr}, viewport{viewport}
{}


QSizeF EffectGraphicalEntity::getSizePx() const
{
	// Not used anyway.
	return QSizeF{0, 0};
}


void EffectGraphicalEntity::setDirection(const BS::Graphic::Direction &direction)
{
	// Not possible for this class.
}


