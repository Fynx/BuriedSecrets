/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtCore>

#include "Common/Enums.hpp"
#include "DataManager/AnimationData.hpp"


class TextureSetData;


class Prototype {
public:
	Prototype();
	~Prototype();

	bool hasProperty(const QString &key) const;
	QVariant getProperty(const QString &key) const;
	void setProperty(const QString &key, const QVariant &value);

	// TODO remove after migrating to new textures.
	const AnimationData *getAnimationData(const BS::State &state) const;
	const QList<const AnimationData *> getAnimationsData() const;
	void addAnimationData(BS::State state, const AnimationData *data);

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

private:
	QMap <QString, QVariant> properties;
	QMap <BS::State, const AnimationData *> animationData;
	QPointF baseCentre;
	QList<QPointF> basePolygon;

	TextureSetData *textureSetData;
};
