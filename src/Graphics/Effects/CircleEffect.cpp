/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Effects/CircleEffect.hpp"

#include "Common/Geometry.hpp"
#include "Graphics/Entities/GraphicalEntity.hpp"


CircleEffect::CircleEffect(const Viewport *viewport, const sf::Color &outlineColor, const sf::Color &fillColor)
	: GraphicalEffect{viewport}
{
	circleShape.setOutlineColor(outlineColor);
	circleShape.setFillColor(fillColor);
	circleShape.setPointCount(20);
	circleShape.setOutlineThickness(1);
}


void CircleEffect::draw(const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget)
{	QPointF scale = viewport->getWholeScale();
	scale /= std::max(scale.x(), scale.y());
	circleShape.setScale(scale.x(), scale.y());

	update(graphicalEntity);

	renderTarget->draw(circleShape);
}


void CircleEffect::setGeometry(const QPointF &position, const float radius)
{
	circleShape.setRadius(radius);
	circleShape.setPointCount(ceil(PointsPerPixel * BS::Geometry::Circle{position, radius}.getLength()));
	sf::FloatRect size = circleShape.getGlobalBounds();
	circleShape.setPosition(sf::Vector2f{(float)position.x() - size.width / 2.0f,
			(float)position.y() - size.height / 2.0f});
}


void CircleEffect::setOutlineThickness(const float thickness)
{
	circleShape.setOutlineThickness(thickness);
}



