/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/BasePolygonEffect.hpp"

#include "Common/Enums.hpp"


BasePolygonEffect::BasePolygonEffect() : GraphicalEffect{}
{
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineThickness(2);
	polygon.setOutlineColor(sf::Color::Red);

	point.setPointCount(4);
	point.setRadius(2);
	point.setFillColor(sf::Color::Yellow);
	point.setOutlineColor(sf::Color::Yellow);
	point.setOutlineThickness(0);
}



void BasePolygonEffect::draw(const GraphicalEntity *graphicalEntity, const QPointF &entityPosition,
			     const Viewport *viewport, sf::RenderTarget *renderTarget)
{
	const auto points = graphicalEntity->getBasePolygon();
	QPointF centre = graphicalEntity->getBaseCentre();
	QPointF upperLeft = entityPosition - centre;

	// Draw the base polygon.
	polygon.setPointCount(points.size());
	for (int i = 0; i < points.size(); ++i) {
		polygon.setPoint(i, sf::Vector2f(upperLeft.x() + points[i].x(), upperLeft.y() + points[i].y()));
	}
	polygon.setOutlineColor(sf::Color::Red);
	renderTarget->draw(polygon);

	// Draw the outline.
	QSizeF size = graphicalEntity->getSizePx();
	polygon.setPointCount(4);
	polygon.setPoint(0, sf::Vector2f(upperLeft.x(), upperLeft.y()));
	polygon.setPoint(1, sf::Vector2f(upperLeft.x() + size.width(), upperLeft.y()));
	polygon.setPoint(2, sf::Vector2f(upperLeft.x() + size.width(), upperLeft.y() + size.height()));
	polygon.setPoint(3, sf::Vector2f(upperLeft.x(), upperLeft.y() + size.height()));
	polygon.setOutlineColor(sf::Color::Magenta);
	renderTarget->draw(polygon);

	// Draw centre.
	point.setPosition(upperLeft.x() + centre.x() - 1, upperLeft.y() + centre.y() - 1);
	renderTarget->draw(point);
}


int BasePolygonEffect::getOrderId() const
{
	return BS::Graphic::EffectOrder::BasePolygon;
}

