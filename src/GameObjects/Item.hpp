/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class Item : public Object {
public:
	static const int StarLimit = 10;

	Item(const Prototype *prototype);

	BS::Type getType() const;

	BS::ItemType getItemType() const;

	QString getName() const;
	int getWeight() const;

	QSet<BS::Slot> getAvailableSlots() const;
	bool isSlotAvailable(BS::Slot slot) const;

	int getUsesLeft();
	void setUsesLeft(int n);

	int getUseDelay();
	void setUseDelay(int t);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	int usesLeft;
	int delay;
};
