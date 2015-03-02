/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once
#include <QPointF>

#include "Mind/EffectData.hpp"


/**
 * @brief This effect data represents a point that describe the effect.
 */
class PointEffectData : public EffectData {
public:
	PointEffectData(const QPointF &point);

	QPointF getPoint() const;

private:
	const QPointF point;
};
