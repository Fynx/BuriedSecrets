/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

/**
 * @class Item
 * Objects that appear only in Equipment.
 * Items can have impact on Units' stats, while in certain slots.
 * Also some Items can be combined to create new Items.
 */
class Item : public Object {
public:
	/** Maximum quality estimate. */
	static const int StarLimit = 10;

	Item(const Prototype *prototype);

	BS::Type getType() const;

	/** Items can have multiple types. */
	QVector<BS::ItemType> getItemTypes() const;

	QString getName() const;
	int getWeight() const;

	/** Given Item can be put only in certain slots. */
	QSet<BS::Slot> getAvailableSlots() const;
	bool isSlotAvailable(BS::Slot slot) const;

	int getUsesLeft();
	void setUsesLeft(int n);

	int getUseDelay();
	void setUseDelay(int t);

	int getMaxDelay();
	void setMaxDelay(int t);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	int usesLeft;
	int delay;
	int maxDelay;
};
