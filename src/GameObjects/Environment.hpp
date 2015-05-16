/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

/**
 * @class Environment
 * Object that doesn't change and doesn't interact with anything.
 * It's either barring the way, reducing visibility, or simply being a decoration.
 */
class Environment : public Object {
public:
	Environment(const Prototype *prototype);

	virtual BS::Type getType() const;

	bool isObstacle() const;
	bool isTransparent() const;

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;
};
