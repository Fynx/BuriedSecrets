/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/EffectData.hpp"

class Object;


/**
 * @brief EffectData for effects which need objects as input.
 */
class ObjectEffectData: public EffectData {
public:
	ObjectEffectData(const Object *object);
	~ObjectEffectData() override;

	const Object *getObject() const;

private:
	const Object *object;
};
