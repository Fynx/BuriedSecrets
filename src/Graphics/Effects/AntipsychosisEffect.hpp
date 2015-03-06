/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "Graphics/Effects/CircleEffect.hpp"


class AntipsychosisEffect : public CircleEffect {
public:
	AntipsychosisEffect(const Viewport *viewport);
	int getOrderId() const override;
	void update(const GraphicalEntity *graphicalEntity) override;
};