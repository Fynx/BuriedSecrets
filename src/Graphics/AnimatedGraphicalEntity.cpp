/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/AnimatedGraphicalEntity.hpp"

using namespace sf;


AnimatedGraphicalEntity::AnimatedGraphicalEntity(const Object *object, const AnimationSet &animationSet)
	: GraphicalEntity{object}, animationSet{animationSet}
{
	// FIXME temporary
	sprite.setScale(0.05, 0.05);
}


Drawable *AnimatedGraphicalEntity::getDrawable()
{
	return &sprite;
}


void AnimatedGraphicalEntity::setPosition(const QPointF &position)
{
	sprite.setPosition(position.x(), position.y());
}


void AnimatedGraphicalEntity::update(const float timeDelta)
{
	// FIXME calculate direction
	int direction = 0;
	sprite.setTexture(*(animationSet.getAnimationForState(
			object->getState())->getFrame(direction, object->getFrame())));
}

