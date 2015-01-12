/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Item.hpp"
#include "Common/Enums.hpp"

class Equipment : public Object {
public:
	Equipment(const Prototype *prototype);

	virtual BS::Type getType() const;

	void addItem(Item *item);
	void removeItem(Item *item);
	const QSet<Item *> &getItems() const;
	int getWeight() const;
	Item *getSlotItem(BS::Slot);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	QSet<Item *> items;
	QHash<BS::Slot, Item*> usedItems;
};
