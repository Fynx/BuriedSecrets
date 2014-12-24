/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "UserInterface/Perspective.hpp"

class IsometricPerspective: public Perspective {
public:
	IsometricPerspective(const float scale);

protected:
	QPointF getOriginalScaledPoint(const QPointF &transformedPoint) const override;
	QPointF getTransformedPoint(const QPointF &scaledPoint) const override;

private:
	const float isometricYScale = 2.0f;
};