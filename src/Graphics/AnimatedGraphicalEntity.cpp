/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/AnimatedGraphicalEntity.hpp"


AnimatedGraphicalEntity::AnimatedGraphicalEntity(const Object *object, const QList<QPointF> &basePolygon,
						 const AnimationSet &animationSet)
	: SpriteGraphicalEntity{object, basePolygon}, animationSet{animationSet}
	, direction{BS::Graphic::Direction::Right}
{}


void AnimatedGraphicalEntity::setDirection(const BS::Graphic::Direction &direction)
{
	this->direction = direction;
}


void AnimatedGraphicalEntity::update(const float timeDelta)
{
	sprite.setTexture(*(animationSet.getAnimationForState(
			object->getState())->getFrame(direction, object->getFrame())));
}

