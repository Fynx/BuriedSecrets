/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "UserInterface/Viewport/Perspective.hpp"

class IsometricPerspective: public Perspective {
public:
	IsometricPerspective(const float scale);

protected:
	QPointF fromPixelsToBase(const QPointF &transformedPoint) const override;
	QPointF fromBaseToPixels(const QPointF &scaledPoint) const override;

private:
	const float isometricYScale = 2.0f;
};
