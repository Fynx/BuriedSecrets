/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <memory>

#include <QString>

#include "Mind/EffectData.hpp"


/**
 * @brief The logical representation of an effect.
 */
class Effect {
public:
	static const int CommandEffectTimeout = 280;	// Empirically set constant.
	/**
	 * @brief Creates an effect with name, data and timeout.
	 *
	 * The object takes ownership of effectData.
	 */
	Effect(const QString &name, EffectData *effectData, int timeout);
	/**
	 * @brief Creates an infinite effect with name and data.
	 *
	 * The object takes ownership of effectData.
	 */
	Effect(const QString &name, EffectData *effectData);

	QString getName() const;
	const EffectData *getEffectData() const;
	int getTimeout() const;
	/**
	 * @brief True if the effect is infinite.
	 */
	bool isInfinite() const;

	void setTimeout(const int timeout);

private:

	QString name;
	std::shared_ptr<EffectData> effectData;
	int timeout;
};
