/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/LineShape.hpp"

#include <cmath>


LineShape::LineShape()
{
	setColor(sf::Color::Transparent);
	setPoints({0, 0}, {0, 0});
	setThickness(0.);
}


LineShape::LineShape(const QPointF &from, const QPointF &to, const sf::Color &color, const float thickness)
	: thickness{thickness}
{
	setPoints(from, to);
	setColor(color);
}


void LineShape::setPoints(const QPointF &from, const QPointF &to)
{
	this->from = from;
	this->to = to;
	QPointF diff = to - from;
	sf::Vector2f p1{(float)from.x(), (float)from.y()};
	sf::Vector2f p2{(float)to.x(), (float)to.y()};
	sf::Vector2f direction{(float)diff.x(), (float)diff.y()};
	sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

	sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

	vertices[0].position = p1 + offset;
	vertices[1].position = p2 + offset;
	vertices[2].position = p2 - offset;
	vertices[3].position = p1 - offset;
}


void LineShape::setColor(const sf::Color &color)
{
	this->color = color;
	for (int i=0; i<4; ++i) {
		vertices[i].color = color;
	}
}


void LineShape::setThickness(const float thickness)
{
	this->thickness = thickness;
	setPoints(this->from, this->to);
}


void LineShape::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(vertices, 4, sf::Quads);
}

