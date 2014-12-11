/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include <cassert>

#include "DataManager/AnimationData.hpp"
#include "GameObjects/Object.hpp"

AnimationData::AnimationData(const QString &name, const QString &rawData)
	: name{name}
{
	QStringList data = rawData.split(" ");
	state = BS::getStateFromString(data.at(0));
	int numFrames = data.at(1).toInt();
	for (int i = 2, dir = 0; i < data.size(); i += numFrames, ++dir) {
		framesDescription.append(QVector<QString>{});
		for (int j = i; j - i < numFrames; ++j) {
			framesDescription[dir].append(data.at(j));
		}
	}

	// Assert that animations in all directions have the same number of frames.
	const auto len = framesDescription[0].length();
	for (int i = 1; i < framesDescription.length(); ++i) {
		assert(framesDescription[i].length() == len);
	}

	qDebug() << "Read " << framesDescription[0].length() << " frames for every direction.";
}


const QString &AnimationData::getName() const
{
	return name;
}


const AnimationData::FramesDescription &AnimationData::getFramesDescription() const
{
	return framesDescription;
}


const BS::State AnimationData::getState() const
{
	return state;
}


const int AnimationData::getFramesForDirection(const int direction) const
{
	return framesDescription.at(direction).length();
}


const int AnimationData::getFramesNumber() const
{
	return framesDescription.at(0).length();
}



