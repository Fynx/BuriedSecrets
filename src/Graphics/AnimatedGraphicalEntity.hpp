/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "Graphics/Animation.hpp"
#include "Graphics/AnimationSet.hpp"
#include "Graphics/GraphicalEntity.hpp"


class AnimatedGraphicalEntity: public GraphicalEntity {
public:
	AnimatedGraphicalEntity(const Object *object, const AnimationSet &animationSet);

	sf::Drawable *getDrawable() override;
	void setPosition(const QPointF &position) override;
	void update(const float timeDelta) override;

private:
	sf::Sprite sprite;
	const AnimationSet animationSet;
};