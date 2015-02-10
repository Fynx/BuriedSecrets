/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class Item : public Object {
public:
	Item(const Prototype *prototype);

	BS::Type getType() const;

	BS::ItemType getItemType() const;
	bool isEquippable() const;

	QString getName() const;
	int getWeight() const;

	int getUsesLeft();
	void setUsesLeft(int n);

	int getUseDelay();
	void setUseDelay(int t);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	int usesLeft;
	int delay;

	static const QMap<BS::ItemType, bool> equippable;
	static const QMap<QString, BS::ItemType> stringToItemType;
};
