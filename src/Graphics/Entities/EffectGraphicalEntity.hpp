/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "Graphics/Entities/GraphicalEntity.hpp"


/**
 * @brief This class represents an abstrac entity effect - a global effect not assigned to any Object.
 */
class EffectGraphicalEntity : public GraphicalEntity {
public:
	EffectGraphicalEntity(const Viewport *viewport);
	virtual void draw(sf::RenderTarget *renderTarget) = 0;
	QSizeF getSizePx() const override;
	void setDirection(const BS::Graphic::Direction &direction) override;
	virtual void update(const float timeDelta) = 0;
	virtual void updateData(const EffectData *effectData) = 0;

protected:
	const Viewport *viewport;

private:
	using GraphicalEntity::addOrMarkEffectActive;
	using GraphicalEntity::resetActiveEffects;
	void removeInactiveEffects();
};