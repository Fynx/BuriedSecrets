/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class QuestLog : public Object {
public:
	QuestLog(const Prototype *prototype);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;
};