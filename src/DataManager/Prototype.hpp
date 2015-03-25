/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtCore>

#include "Common/Enums.hpp"


class TextureSetData;


class Prototype {
public:
	Prototype();
	~Prototype();

	bool hasProperty(const QString &key) const;
	QVariant getProperty(const QString &key) const;
	void setProperty(const QString &key, const QVariant &value);

	const TextureSetData *getTextureSetData() const;
	/**
	 * @brief Sets the texture set data for the Prototype.
	 * This method deletes the data stored previously (invalidating any pointer to it!) and then replaces the
	 * previously held object with the new one. This method takes ownership of the passed pointer.
	 */
	void setTextureSetData(TextureSetData *textureSetData);

	/**
	 * @brief Returns the base centre. Only valid for prototypes that have this field.
	 */
	const QPointF getBaseCentre() const;
	/**
	 * @brief Returns the base polygon. Only valid for prototypes that have this field.
	 */
	const QList<QPointF> getBasePolygon() const;

	void setBaseCentre(const QPointF &baseCentre);
	void setBasePolygon(const QList<QPointF> &basePolygon);

	void loadFromJson(const QJsonObject &json);
	QJsonObject saveToJson() const;

private:
	QMap <QString, QVariant> properties;
	QPointF baseCentre;
	QList<QPointF> basePolygon;

	TextureSetData *textureSetData;
};
