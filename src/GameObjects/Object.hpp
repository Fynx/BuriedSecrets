/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "DataManager/Prototype.hpp"

/**
 * @class Object
 * Represents everything serializable in the game.
 * Doesn't necessarily appear on the map, it can be an entry in a journal or container like equipment.
 */
class Object {
public:
	Object(const Prototype *prototype);
	virtual ~Object();

	/** Every Object needs an UID. */
	static const int InvalidUid = 0;
	/** If current UID is invalid, new UID is assigned. */
	int assignUid();
	int getUid() const;

	/** If it's possible that the Object shouldn't be saved during map save. */
	virtual bool isRemovable() const;
	/** Every Object has a prototype set in constructor. */
	const Prototype *getPrototype() const;

	/** In order to recognize the subclass of given Object, every subclass needs to implement this function. */
	virtual BS::Type getType() const = 0;
	QString getName() const;

	/** Faction to which the Object belongs to. Faction Objects point at themselves. */
	int getFactionId() const;
	void setFactionId(const int factionId);

	/** What is currently happening with this Object. */
	BS::State getState() const;
	void setState(BS::State state);

	/** Temporary values used and set by animators. */
	QVariant &property(const QString &name);
	const QVariant property(const QString &name) const;

	int getFrame() const;
	void setFrame(int frame);

	/**
	 * Every Object needs a customized function to save / load it from json.
	 * This is an interface for that.
	 */
	virtual void loadFromJson(const QJsonObject &json) = 0;
	virtual QJsonObject saveToJson() const = 0;

protected:
	const Prototype *prototype;

	static void updateUid(int uid);
	/** Every new UID is greater than every previous */
	static int LastUid;

	int uid;

	int factionId;
	BS::State state;
	int frame;
	QMap <QString, QVariant> properties;
};
