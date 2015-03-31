/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "Graphics/Effects/CircleEffect.hpp"


class AntipsychosisEffect : public CircleEffect {
public:
	AntipsychosisEffect(const Viewport *viewport, const float radius);
	int getOrderId() const override;
	void update(const GraphicalEntity *graphicalEntity) override;

private:
	const float radius;
};