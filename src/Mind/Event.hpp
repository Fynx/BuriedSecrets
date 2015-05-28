/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include <QtCore>

/**
 * @class Event
 * Originally a container describing what just occurred.
 * Events are deprecated in favour of doing everything in specific Animators.
 */
class Event {
public:
	Event(const QString &name = QString());
	QString toString() const;

private:
	QString name;
};
