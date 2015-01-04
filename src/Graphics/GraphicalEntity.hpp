/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "GameObjects/Object.hpp"


/**
 * @brief The graphical representation of the logical object.
 *
 */
class GraphicalEntity {
public:
	GraphicalEntity(const Object *object, QList<QPointF> basePolygon);
	virtual ~GraphicalEntity();

	virtual sf::Drawable *getDrawable() = 0;
	/**
	 * @brief Sets the Entity's position.
	 *
	 * @param position In pixels.
	 */
	virtual void setPosition(const QPointF &position) = 0;
	virtual void setDirection(const BS::Graphic::Direction &direction) = 0;
	const Object* getObject() const;
	QList<QPointF> getBasePolygon() const;
	QPointF getBaseCentre() const;
	/**
	 * @brief Updates the internal state of the Entity over the time that has passed since the last update.
	 *
	 * @param timeDelta Time since the last update (in ms).
	 * @return void
	 */
	virtual void update(const float timeDelta) = 0;

protected:
	const Object *object;
	QList<QPointF> basePolygon;
	QPointF baseCentre;
};