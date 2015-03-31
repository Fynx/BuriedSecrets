/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/EffectData.hpp"


class Object;


class ObjectEffectData : public EffectData {
public:
	ObjectEffectData(const Object *object);
	~ObjectEffectData() override;

	const Object *getObject() const;

private:
	const Object *object;
};