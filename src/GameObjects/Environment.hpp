/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class Environment : public Object {
public:
	Environment(const Prototype *prototype);

	BS::Type getType() const;

	bool isObstacle() const;
	bool isTransparent() const;

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;
};
