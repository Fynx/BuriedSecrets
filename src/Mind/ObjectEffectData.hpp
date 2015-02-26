/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "GameObjects/Object.hpp"
#include "Mind/EffectData.hpp"


class ObjectEffectData : public EffectData {
public:
	ObjectEffectData(const Object *object);
	~ObjectEffectData() override;

	const Object *getObject() const;

private:
	const Object *object;
};