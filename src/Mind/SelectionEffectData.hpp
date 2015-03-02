/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QColor>
#include "Mind/ObjectEffectData.hpp"


class SelectionEffectData : public ObjectEffectData {
public:
	SelectionEffectData(const Object *object, const QColor color);

	QColor getColor() const;

private:
	const QColor color;
};