/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include <QtCore>

class JournalEntry;

/**
 * @brief Logical representation of the map.
 */
class Map {
public:
	Map(const QJsonObject &json);

	const QJsonObject &getJson() const;
	/**
	 * @brief True if point (x, y) can be stepped on. False otherwise.
	 */
	bool canStepAt(const float x, const float y) const;
	/**
	 * @brief True if the coordinates represent a valid point on the map.
	 */
	bool isPointValid(const QPointF &point) const;

	const QString &getName() const;
	const QString &getDesc() const;
	const QString &getTitle() const;
	const QString &getText() const;
	const QSizeF &getSize() const;

private:
	QJsonObject json;
	QString name;
	QString desc;
	QString title;
	QString text;
	QSizeF size;
};
