/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <SFML/Graphics.hpp>

#include "Graphics/Entities/GraphicalEntity.hpp"


class SpriteGraphicalEntity: public GraphicalEntity {
public:
	SpriteGraphicalEntity(const Object *object, const QList<QPointF> &basePolygon,
				GraphicalEffectFactory *graphicalEffectFactory);

	void draw(sf::RenderTarget *renderTarget) override;
	void setPosition(const QPointF &position) override;
	QSizeF getSizePx() const override;
	virtual void setDirection(const BS::Graphic::Direction &direction) = 0;

protected:
	sf::Sprite sprite;
};