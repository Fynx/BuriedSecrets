/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QSet>
#include <SFML/Graphics.hpp>

#include "GameObjects/Object.hpp"
#include "Graphics/GraphicalEffectFactory.hpp"
#include "Graphics/GraphicalEffect.hpp"
#include "Mind/Effect.hpp"


/**
 * @brief The graphical representation of the logical object.
 *
 */
class GraphicalEntity {
public:
	GraphicalEntity(const Object *object, QList<QPointF> basePolygon,
			GraphicalEffectFactory *graphicalEffectFactory);
	virtual ~GraphicalEntity();

	void drawPreEffects(sf::RenderTarget *renderTarget);
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
	virtual void setDirection(const BS::Graphic::Direction &direction) = 0;
	const Object* getObject() const;
	QList<QPointF> getBasePolygon() const;
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