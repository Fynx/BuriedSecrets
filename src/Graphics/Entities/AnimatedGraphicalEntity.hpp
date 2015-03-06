/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "Graphics/Entities/Animation.hpp"
#include "Graphics/Entities/AnimationSet.hpp"
#include "Graphics/Entities/SpriteGraphicalEntity.hpp"


class AnimatedGraphicalEntity: public SpriteGraphicalEntity {
public:
	AnimatedGraphicalEntity(const Object *object, const QList<QPointF> &basePolygon,
				GraphicalEffectFactory *graphicalEffectFactory, const AnimationSet &animationSet);

	void setDirection(const BS::Graphic::Direction &direction) override;
	void update(const float timeDelta) override;

private:
	const AnimationSet animationSet;
	BS::Graphic::Direction direction;
};