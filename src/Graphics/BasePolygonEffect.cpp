/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/BasePolygonEffect.hpp"

#include "Common/Enums.hpp"


void BasePolygonEffect::draw(const GraphicalEntity *graphicalEntity, const QPointF &entityPosition,
			     const Viewport *viewport, sf::RenderTarget *renderTarget)
{
	const auto points = graphicalEntity->getBasePolygon();
	QPointF centre = graphicalEntity->getBaseCentre();
	polygon.setPointCount(points.size());
	for (int i = 0; i < points.size(); ++i) {
		polygon.setPoint(i,
				 sf::Vector2f(entityPosition.x() - centre.x() + points[i].x(),
					      entityPosition.y() - centre.y() + points[i].y()));
	}
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineThickness(2);
	polygon.setOutlineColor(sf::Color::Red);
	renderTarget->draw(polygon);
}


int BasePolygonEffect::getOrderId() const
{
	return BS::Graphic::EffectOrder::BasePolygon;
}

