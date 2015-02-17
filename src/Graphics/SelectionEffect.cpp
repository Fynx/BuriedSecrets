/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/SelectionEffect.hpp"

#include "Graphics/Common.hpp"
#include "Common/Strings.hpp"


SelectionEffect::SelectionEffect() : Effect{}
{
	circleShape.setPointCount(20);
	circleShape.setFillColor(sf::Color::Transparent);
	circleShape.setOutlineColor(sf::Color::Cyan);
	circleShape.setOutlineThickness(1);
}


void SelectionEffect::draw(const GraphicalEntity *graphicalEntity, const QPointF &entityPosition,
			   const Viewport *viewport, sf::RenderTarget *renderTarget)
{
	const Object *obj = graphicalEntity->getObject();
	if (obj->property(TempData::IsSelected).toBool()) {
		auto objType = obj->getPrototype()->getProperty("type").toString();
		QPointF centre = graphicalEntity->getBaseCentre();
		float radius = 0.0f;
		if (objType == "unit") {
			radius = obj->getPrototype()->getProperty("baseRadius").toFloat();
		} else {
			basePolygon = graphicalEntity->getBasePolygon();
			for (const QPointF &p: basePolygon) {
				radius = std::max(radius, BS::Graphic::distance(p, centre));
			}
		}

		QPointF scale = viewport->getWholeScale();
		float radiusPx = std::max(radius * scale.x(), radius * scale.y());

		scale /= std::min(scale.x(), scale.y());
		circleShape.setScale(scale.x(),  scale.y());
		float maxNormScale = std::max(scale.x(), scale.y());

		QPointF radiusDelta{radiusPx * scale.x() / maxNormScale,
				radiusPx * scale.y() / maxNormScale};
		centre.setX(centre.x() * scale.x() / maxNormScale);
		centre.setY(centre.y() * scale.y() / maxNormScale);

		centre = entityPosition - centre - radiusDelta;
		circleShape.setPosition(centre.x(), centre.y());
		circleShape.setRadius(radiusPx);
		renderTarget->draw(circleShape);
	}
}


int SelectionEffect::getOrderId() const
{
	return BS::Graphic::EffectOrder::Selection;
}
