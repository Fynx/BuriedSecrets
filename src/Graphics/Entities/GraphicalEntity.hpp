/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QMultiMap>
#include <QPointF>
#include <QSet>
#include <QSizeF>
#include <SFML/Graphics.hpp>

#include "Common/Enums.hpp"
#include "Graphics/Effects/GraphicalEffect.hpp"

class Effect;
class EffectData;
class GraphicalEffectFactory;
class Object;


/**
 * @brief A graphical representation of a logical object.
 */
class GraphicalEntity {
public:
	GraphicalEntity(const Object *object, QList<QPointF> basePolygon,
			GraphicalEffectFactory *graphicalEffectFactory);
	virtual ~GraphicalEntity();

	/**
	 * @brief Draws effects for the Entity that are supposed to appear before (under) it.
	 */
	void drawPreEffects(sf::RenderTarget *renderTarget);
	/**
	 * @brief Draws effects for the Entity that are supposed to appear after (above) it.
	 */
	void drawPostEffects(sf::RenderTarget *renderTarget);
	virtual void draw(sf::RenderTarget *renderTarget) = 0;
	/**
	 * @brief Sets the Entity's position.
	 *
	 * @param position In pixels.
	 */
	virtual void setPosition(const QPointF &position);
	/**
	 * @brief Returns the newest known screen position of the entity.
	 */
	QPointF getPosition() const;
	/**
	 * @brief Sets the direction of the Entity.
	 *
	 * If there are textures for the given direction, during the next redraw, this entity should use them.
	 */
	virtual void setDirection(const BS::Graphic::Direction &direction) = 0;
	const Object* getObject() const;
	/**
	 * @brief Returns the Entity's base polygon (in logical coordinates, relative to the upper left corner of the
	 * texture).
	 */
	QList<QPointF> getBasePolygon() const;
	/**
	 * @brief Returns the Entity's base centre (in logical coordinates, relative to the upper left corner of the
	 * texture).
	 */
	QPointF getBaseCentre() const;
	/**
	 * @brief Returns the size of the actual texture that is drawn on the screen.
	 */
	virtual QSizeF getSizePx() const = 0;
	/**
	 * @brief Updates the internal state of the Entity over the time that has passed since the last update.
	 *
	 * @param timeDelta Time since the last update (in ms).
	 * @return void
	 */
	virtual void update(const float timeDelta) = 0;

	/**
	 * @brief Resets the activeness markers for all effects.
	 */
	void resetActiveEffects();
	/**
	 * @brief Adds an effect or if it already was added, marks it as active.
	 */
	void addOrMarkEffectActive(const Effect &effect);
	/**
	 * @brief Removes effects not marked active.
	 */
	void removeInactiveEffects();
;
protected:
	const Object *object;
	QList<QPointF> basePolygon;
	QPointF baseCentre;
	QPointF position;

private:
	typedef const EffectData * EffectId;
	typedef QMultiMap<int, GraphicalEffect *> EffectsMap;
	void drawEffects(sf::RenderTarget *renderTarget, EffectsMap &effectsMap);
	void removeInactiveEffects(EffectsMap &effectsMap);
	void removeEffect(EffectsMap &effectsMap, GraphicalEntity::EffectId effectId, EffectsMap::iterator iter);

	GraphicalEffectFactory *graphicalEffectFactory;
	QSet<EffectId> activeEffects;
	QSet<EffectId> presentEffects;
	EffectsMap preEffects;
	EffectsMap postEffects;
	QHash<GraphicalEffect *, EffectId> reverseMap;
};
