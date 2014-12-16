/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Item.hpp"

class Equipment : public Object {
public:
	Equipment(const Prototype *prototype);

	virtual BS::Type getType() const;

	void addItem(Item *item);
	void removeItem(Item *item);
	const QSet<Item *> &getItems() const;
	int getWeight() const;

private:
	QSet<Item *> items;
};
