/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/Perspective.hpp"

Perspective::Perspective(const float scale)
	: scale{scale}
{}


QPointF Perspective::getLogicalPoint(const QPointF &translatedPoint) const
{
	return scalePoint(getOriginalScaledPoint(translatedPoint), 1.0f / scale);
}


QPointF Perspective::getTranslatedPoint(const QPointF &logicalPoint) const
{
	return getTransformedPoint(scalePoint(logicalPoint, scale));
}


QRectF Perspective::getLogicalRect(const QRectF& translatedRect) const
{
	return QRectF(
		getLogicalPoint(translatedRect.topLeft()),
		getLogicalPoint(translatedRect.bottomRight())
	);
}


QRectF Perspective::getTranslatedRect(const QRectF& logicalRect) const
{
	return QRectF(
		getTranslatedPoint(logicalRect.topLeft()),
		getTranslatedPoint(logicalRect.bottomRight())
	);
}


QPointF Perspective::scalePoint(const QPointF &orig, const float useScale) const
{
	return orig * useScale;
}




