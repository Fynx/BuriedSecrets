/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/Viewport/Perspective.hpp"


Perspective::Perspective(const float pixelToMetresScale)
	: pixelToMetresScale{pixelToMetresScale}
{}


QPointF Perspective::fromPixelsToMetres(const QPointF &translatedPoint) const
{
	return fromBaseToMetres(fromPixelsToBase(translatedPoint));
}


QPointF Perspective::fromMetresToPixels(const QPointF &logicalPoint) const
{
	return fromMetresToBase(fromBaseToPixels(logicalPoint));
}


QRectF Perspective::fromPixelsToMetres(const QRectF &translatedRect) const
{
	return QRectF(
		fromPixelsToMetres(translatedRect.topLeft()),
		fromPixelsToMetres(translatedRect.bottomRight())
	);
}


QRectF Perspective::fromMetresToPixels(const QRectF &logicalRect) const
{
	return QRectF(
		fromMetresToPixels(logicalRect.topLeft()),
		fromMetresToPixels(logicalRect.bottomRight())
	);
}


QPointF Perspective::fromMetresToBase(const QPointF &originalPoint) const
{
	return scalePoint(originalPoint, pixelToMetresScale);
}


QPointF Perspective::fromBaseToMetres(const QPointF &scaledPoint) const
{
	return scalePoint(scaledPoint, 1.0f / pixelToMetresScale);
}


QRectF Perspective::fromBaseToMetres(const QRectF &scaledRect) const
{
	return QRectF(
		fromBaseToMetres(scaledRect.topLeft()),
		fromBaseToMetres(scaledRect.bottomRight())
	);
}


QRectF Perspective::fromMetresToBase(const QRectF &originalRect) const
{
	return QRectF(
		fromMetresToBase(originalRect.topLeft()),
		fromMetresToBase(originalRect.bottomRight())
	);
}


QSizeF Perspective::fromMetresToPixels(const QSizeF &sizeInMetres) const
{
	return pointToSize(fromMetresToPixels(sizeToPoint(sizeInMetres)));
}


QSizeF Perspective::fromPixelsToMetres(const QSizeF &sizeInPixels) const
{
	return pointToSize(fromPixelsToMetres(sizeToPoint(sizeInPixels)));
}


QPointF Perspective::scalePoint(const QPointF &orig, const float scale) const
{
	return orig * scale;
}


QPointF Perspective::sizeToPoint(const QSizeF &size) const
{
	return QPointF{size.width(), size.height()};
}


QSizeF Perspective::pointToSize(const QPointF &point) const
{
	return QSizeF{point.x(), point.y()};
}
