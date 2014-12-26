/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore/QPointF>
#include <QtCore/QRectF>

/**
 * @brief This class represents an implementation of a perspective.
 */
class Perspective {
public:
	Perspective(const float scale);
	virtual ~Perspective() = default;

	QPointF getLogicalPoint(const QPointF &translatedPoint) const;
	QPointF getTranslatedPoint(const QPointF &logicalPoint) const;
	QRectF getLogicalRect(const QRectF &translatedRect) const;
	QRectF getTranslatedRect(const QRectF &logicalRect) const;

protected:
	virtual QPointF getTransformedPoint(const QPointF &scaledPoint) const = 0;
	virtual QPointF getOriginalScaledPoint(const QPointF &transformedPoint) const = 0;

private:
	QPointF scalePoint(const QPointF &orig, const float useScale) const;

	const float scale;
};