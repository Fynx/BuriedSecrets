/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtCore>

#include "Common/Enums.hpp"
#include "DataManager/AnimationData.hpp"

class Prototype {
public:
	Prototype() = default;

	bool hasProperty(const QString &key) const;
	QVariant getProperty(const QString &key) const;
	void setProperty(const QString &key, const QVariant &value);
	const AnimationData *getAnimationData(const BS::State &state) const;
	const QList< const AnimationData * > getAnimationsData() const;
	void addAnimationData(const BS::State &state, const AnimationData* data);

private:
	QMap <QString, QVariant> properties;
	QMap <BS::State, const AnimationData *> animationData;
};