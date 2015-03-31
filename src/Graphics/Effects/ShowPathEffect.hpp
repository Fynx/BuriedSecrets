/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Graphics/Common/LineShape.hpp"
#include "Graphics/Effects/GraphicalEffect.hpp"


class ShowPathEffect : public GraphicalEffect {
public:
	ShowPathEffect(const Viewport *viewport);
	void draw(const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget) override;
	int getOrderId() const;

private:
	LineShape line;
	sf::RectangleShape pointShape;
};
