/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "GameObjects/Object.hpp"
#include "Mind/ObjectEffectData.hpp"
#include <QPointF>


class ShotEffectData : public ObjectEffectData {
public:
	ShotEffectData(const Object *object, QPointF destination);
	virtual ~ShotEffectData();

	QPointF getDestination() const;

private:
	const QPointF dest;
};
