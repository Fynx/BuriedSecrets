/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtCore>

class Event {
public:
	Event(const QString &name = QString());
	QString toString() const;

private:
	//TODO change to sth useful
	QString name;
};