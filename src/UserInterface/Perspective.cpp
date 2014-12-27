/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/Perspective.hpp"

Perspective::Perspective(const float scale)
	: scale{scale}
{}


QPointF Perspective::getLogicalPoint(const QPointF &translatedPoint) const
{
	return getOriginalPoint(getOriginalScaledPoint(translatedPoint));
}


QPointF Perspective::getTranslatedPoint(const QPointF &logicalPoint) const
{
	return getScaledPoint(getTransformedPoint(logicalPoint));
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


QPointF Perspective::getScaledPoint(const QPointF &originalPoint) const
{
	return scalePoint(originalPoint, scale);
}


QPointF Perspective::getOriginalPoint(const QPointF &scaledPoint) const
{
	return scalePoint(scaledPoint, 1.0f / scale);
}


QRectF Perspective::getOriginalRect(const QRectF &scaledRect) const
{
	return QRectF(
		getOriginalPoint(scaledRect.topLeft()),
		getOriginalPoint(scaledRect.bottomRight())
	);
}


QRectF Perspective::getScaledRect(const QRectF &originalRect) const
{
	return QRectF(
		getScaledPoint(originalRect.topLeft()),
		getScaledPoint(originalRect.bottomRight())
	);
}


QPointF Perspective::scalePoint(const QPointF &orig, const float useScale) const
{
	return orig * useScale;
}



