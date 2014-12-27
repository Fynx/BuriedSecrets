/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/AnimationData.hpp"
#include "GameObjects/Object.hpp"

AnimationData::AnimationData(
	const QString &name,
	BS::State state,
	int framesNumber,
	const QVariantList &frames)
	: name(name), state(state), framesNumber(framesNumber)
{
	FramesDescription desc;
	for (int i = 0, dir = 0; i < frames.size(); i += framesNumber, ++dir) {
		framesDescription.append(QVector<QString>{});
		for (int j = i; j - i < framesNumber; ++j)
			framesDescription[dir].append(frames[j].toString());
	}

	// Assert that animations in all directions have the same number of frames.
	const auto len = framesDescription[0].length();
	for (int i = 1; i < framesDescription.length(); ++i)
		Q_ASSERT(framesDescription[i].length() == len);

	qDebug() << "Read" << framesDescription[0].length() << "frames for every direction.";
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
