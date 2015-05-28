/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QPointF>
#include <SFML/Graphics.hpp>


/**
 * @brief This class represents a segment between two points.
 *
 * An instance of this class can be drawn like any other SFML Drawable.
 */
class LineShape: public sf::Drawable
{
public:
	LineShape();
	LineShape(const QPointF &from, const QPointF &to, const sf::Color &color, const float thickness);

	void setPoints(const QPointF &from, const QPointF &to);
	void setColor(const sf::Color &color);
	void setThickness(const float thickness);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	QPointF from;
	QPointF to;
	sf::Vertex vertices[4];
	float thickness;
	sf::Color color;
};
