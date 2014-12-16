/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "DataManager/Prototype.hpp"

class Object {
public:
	Object(const Prototype *prototype);
	virtual ~Object();

	const int getUid() const;
	const Prototype *getPrototype() const;

	virtual BS::Type getType() const = 0;

	Object *getParent() const;
	void setParent(Object *object);

	BS::State getState() const;
	void setState(BS::State state);

	//TODO
	// Number 'frame' represents the current frame in the current action.
	// Animators update the frames.
	// Either they need to know about the max number of frames for the action
	// or it must be controlled in these functions making them non-trivial accessors.
	int getFrame() const;
	void setFrame(int frame);

protected:
	const Prototype *prototype;

private:
	friend QDataStream &operator<<(QDataStream &out, const Object &object);
	friend QDataStream &operator>>(QDataStream &in, Object &object);

	static int LastUid;

	// Watch for all traps connected to serialization!
	const int uid;

	Object *parent;
	BS::State state;
	int frame;
};
