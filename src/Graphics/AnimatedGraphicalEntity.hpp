/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "Graphics/Animation.hpp"
#include "Graphics/AnimationSet.hpp"
#include "Graphics/SpriteGraphicalEntity.hpp"


class AnimatedGraphicalEntity: public SpriteGraphicalEntity {
public:
	AnimatedGraphicalEntity(const Object *object, const QList<QPointF> &basePolygon,
				const AnimationSet &animationSet);

	void setDirection(const BS::Graphic::Direction &direction) override;
	void update(const float timeDelta) override;

private:
	const AnimationSet animationSet;
	BS::Graphic::Direction direction;
};