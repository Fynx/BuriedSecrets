/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Graphics/Effects/CircleEffect.hpp"


/**
 * @brief This class represents the Antipsychosis effect.
 *
 * It's a circular effect with preset violet color.
 */
class AntipsychosisEffect: public CircleEffect {
public:
	AntipsychosisEffect(const Viewport *viewport, const float radius);
	int getOrderId() const override;
	void update(const GraphicalEntity *graphicalEntity) override;

private:
	const float radius;
};
