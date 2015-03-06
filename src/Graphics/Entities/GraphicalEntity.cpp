/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Entities/GraphicalEntity.hpp"


GraphicalEntity::GraphicalEntity(const Object *object, QList<QPointF> basePolygon,
				 GraphicalEffectFactory *graphicalEffectFactory)
	: object{object}, basePolygon{basePolygon}, graphicalEffectFactory{graphicalEffectFactory}
{
	baseCentre = QPointF{0, 0};
	for (const QPointF &p: basePolygon) {
		baseCentre += p;
	}

	baseCentre /= basePolygon.size();
}


GraphicalEntity::~GraphicalEntity()
{
	qDeleteAll(preEffects.values());
	qDeleteAll(postEffects.values());
}


void GraphicalEntity::drawPreEffects(sf::RenderTarget *renderTarget)
{
	drawEffects(renderTarget, preEffects);
}


void GraphicalEntity::drawPostEffects(sf::RenderTarget *renderTarget)
{
	drawEffects(renderTarget, postEffects);
}


void GraphicalEntity::setPosition(const QPointF &position)
{
	this->position = position;
}


QPointF GraphicalEntity::getPosition() const
{
	return position;
}


const Object *GraphicalEntity::getObject() const
{
	return object;
}


QList< QPointF > GraphicalEntity::getBasePolygon() const
{
	return basePolygon;
}


QPointF GraphicalEntity::getBaseCentre() const
{
	return baseCentre;
}


void GraphicalEntity::resetActiveEffects()
{
	activeEffects.clear();
}


void GraphicalEntity::addOrMarkEffectActive(const Effect &effect)
{
	EffectId p = effect.getEffectData();
	if (!presentEffects.contains(p)) {
		GraphicalEffect *graphicalEffect = graphicalEffectFactory->get(effect);
		if (graphicalEffect == nullptr) {
			return;	// Effect not supported.
		}
		EffectsMap &effectsMap = graphicalEffectFactory->isPreEffect(effect) ?
				preEffects: postEffects;
// 		if (effectsMap.contains()) {
// 			// Remove the old effect.
// 			auto iter = effectsMap.find(graphicalEffect->getOrderId());
// 			removeEffect(effectsMap, reverseMap[iter.value()], iter);
// 		}
		effectsMap.insertMulti(graphicalEffect->getOrderId(), graphicalEffect);
		reverseMap[graphicalEffect] = p;
		presentEffects.insert(p);
	}
	activeEffects.insert(p);
}


void GraphicalEntity::removeInactiveEffects()
{
	removeInactiveEffects(preEffects);
	removeInactiveEffects(postEffects);
}


void GraphicalEntity::removeInactiveEffects(EffectsMap &effectsMap)
{
	for (auto it = effectsMap.begin(); it != effectsMap.end();) {
		const auto p = reverseMap[it.value()];
		if (!activeEffects.contains(p)) {
			// Effect is inactive.
			removeEffect(effectsMap, p, it++);
		} else {
			++it;
		}
	}
}


void GraphicalEntity::drawEffects(sf::RenderTarget *renderTarget, EffectsMap &effectsMap)
{
	for (auto *effect : effectsMap) {
		effect->draw(this, renderTarget);
	}
}


void GraphicalEntity::removeEffect(EffectsMap &effectsMap, EffectId effectId, EffectsMap::iterator iter)
{
	presentEffects.remove(effectId);
	reverseMap.remove(iter.value());
	delete iter.value();
	effectsMap.erase(iter);
}


