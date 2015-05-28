/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QPointF>

#include "Mind/EffectData.hpp"


/**
 * @brief This effect data represents an ordered pair of points that describe the effect.
 */
class PointToPointEffectData : public EffectData {
public:
	PointToPointEffectData(const QPointF &source, const QPointF &destination);

	QPointF getSource() const;
	QPointF getDestination() const;

private:
	const QPointF source;
	const QPointF destination;
};
