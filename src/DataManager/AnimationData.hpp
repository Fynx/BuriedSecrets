/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore/QHash>
#include <QtCore/QString>
#include <QVector>

#include "Common/Enums.hpp"


class AnimationData {
public:
	typedef QVector<QVector<QString>> FramesDescription;

	AnimationData(const QString &name, const QString &rawData);

	const QString &getName() const;
	const FramesDescription &getFramesDescription() const;
	const BS::State getState() const;
	const int getFramesForDirection(const int direction) const;
	const int getFramesNumber() const;

private:
	const QString name;
	BS::State state;
	FramesDescription framesDescription;
};