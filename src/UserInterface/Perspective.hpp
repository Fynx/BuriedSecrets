/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore/QPointF>
#include <QtCore/QRectF>

/**
 * @brief This class represents an implementation of a perspective.
 *
 * Pixels - what we see on the screen (isometric).
 * Base - Pixels scaled to physical dimensions.
 * Metres - The logical coordinates.
 */
class Perspective {
public:
	Perspective(const float pixelToMetresScale);
	virtual ~Perspective() = default;

	// Those methods do everything - pixels <-> base <-> metres
	QPointF fromPixelsToMetres(const QPointF &translatedPoint) const;
	QPointF fromMetresToPixels(const QPointF &logicalPoint) const;
	QRectF fromPixelsToMetres(const QRectF &translatedRect) const;
	QRectF fromMetresToPixels(const QRectF &logicalRect) const;
	QSizeF fromMetresToPixels(const QSizeF &sizeInMetres) const;
	QSizeF fromPixelsToMetres(const QSizeF &sizeInPixels) const;

	// Those do just base <-> metres
	QPointF fromMetresToBase(const QPointF &originalPoint) const;
	QPointF fromBaseToMetres(const QPointF &scaledPoint) const;
	QRectF fromMetresToBase(const QRectF &originalRect) const;
	QRectF fromBaseToMetres(const QRectF &scaledRect) const;

protected:
	virtual QPointF fromBaseToPixels(const QPointF &scaledPoint) const = 0;
	virtual QPointF fromPixelsToBase(const QPointF &transformedPoint) const = 0;

private:
	inline QPointF scalePoint(const QPointF &orig, const float scale) const;
	inline QPointF sizeToPoint(const QSizeF &size) const;
	inline QSizeF pointToSize(const QPointF &point) const;

	const float pixelToMetresScale;
};
