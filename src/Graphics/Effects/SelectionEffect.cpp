/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Effects/SelectionEffect.hpp"

#include "Common/Geometry.hpp"
#include "Common/Strings.hpp"
#include "Graphics/Entities/GraphicalEntity.hpp"


SelectionEffect::SelectionEffect(const Viewport *viewport, const sf::Color &color) : CircleEffect{viewport, color}
{
	setOutlineThickness(1.5f);
}


int SelectionEffect::getOrderId() const
{
	return BS::Graphic::EffectOrder::Selection;
}


void SelectionEffect::update(const GraphicalEntity *graphicalEntity)
{
	const Object *obj = graphicalEntity->getObject();
	auto objType = obj->getType();
	float radiusPx = 0.0f;
	QPointF scale = viewport->getWholeScale();

	if (objType == BS::Type::Unit) {
		float radius = obj->getPrototype()->getProperty(Properties::BaseRadius).toFloat();
		radiusPx = std::max(radius * scale.x(), radius * scale.y());
	} else {
		QPointF centre = graphicalEntity->getBaseCentre();
		basePolygon = graphicalEntity->getBasePolygon();
		for (const QPointF &p: basePolygon) {
			radiusPx = std::max(radiusPx, BS::Geometry::distance(p, centre));
		}
	}

	setGeometry(graphicalEntity->getPosition(), radiusPx * 1.5f);
}

