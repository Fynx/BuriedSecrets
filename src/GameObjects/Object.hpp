/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "DataManager/Prototype.hpp"


class Object {
public:
	Object(const Prototype *prototype);
	virtual ~Object();

	/** If current UID is invalid, new UID is assigned. */
	void assignUid();
	int getUid() const;
	const Prototype *getPrototype() const;

	virtual BS::Type getType() const = 0;
	QString getName() const;

	int getFaction() const;
	void setFaction(int faction);

	BS::State getState() const;
	void setState(BS::State state);

	QVariant &property(const QString &name);

	//TODO
	// Number 'frame' represents the current frame in the current action.
	// Animators update the frames.
	// Either they need to know about the max number of frames for the action
	// or it must be controlled in these functions making them non-trivial accessors.
	int getFrame() const;
	void setFrame(int frame);

	virtual void loadFromJson(const QJsonObject &json) = 0;
	virtual QJsonObject saveToJson() const = 0;

protected:
	const Prototype *prototype;

	static void updateUid(int uid);
	static const int InvalidUid = 0;
	/** Every new UID is greater than every previous */
	static int LastUid;

	int uid;

	int factionId;
	BS::State state;
	int frame;
	QMap <QString, QVariant> properties;
};
