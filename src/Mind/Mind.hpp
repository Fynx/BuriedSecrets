/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore>

#include "DataManager/DataManager.hpp"
#include "GameObjects/Object.hpp"
#include "GameObjects/Faction.hpp"
#include "Mind/Animators/AnimatorManager.hpp"
#include "Mind/Effect.hpp"
#include "Mind/Event.hpp"
#include "Mind/ItemConstructor.hpp"
#include "Mind/MapManager/MapManager.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "SoundsManager/SoundsManager.hpp"


class Mind : public QObject {

Q_OBJECT
public:
	static const int PlayerFactionId;

	Mind(DataManager *dataManager, PhysicsEngine *physicsEngine, SoundsManager *soundsManager);
	~Mind();

	PhysicsEngine *physicsEngine();
	ItemConstructor *itemConstructor();

	void loadFromJson(const QJsonObject &json);
	QJsonObject saveToJson() const;

	const Map *getMap() const;
	MapManager *getMapManager() const;

	/**
	 * @brief Adds an object to the inner collection and to physics.
	 *
	 * @param object The object to add.
	 * @param position The position at which it should initially be (physics).
	 * @return void
	 */
	void addObject(Object* object, const QPointF &position);
	void addObject(Object* object);
	Object *createDefaultObject(BS::Type type, QString prototype);
	void removeObject(Object *object);

	Object *getObjectFromUid(const int uid);
	const Object *getObjectFromUid(const int uid) const;
	Faction *getFactionById(const int id);
	const Faction *getFactionById(const int id) const;
	Faction *getPlayerFaction();
	const Faction *getPlayerFaction() const;

	void pauseGame();
	void resumeGame();

	QLinkedList<Effect> * const getActiveEffects();
	QLinkedList<Effect>::iterator addEffect(const Effect &effect);
	/**
	 * @brief Deletes the effect from the list.
	 *
	 * Warning: This method invalidates (only) the passed iterator.
	 */
	void deleteEffect(QLinkedList<Effect>::iterator effectIterator);

	void toggleBasePolygons();

private:
	Object *createObject(BS::Type type, const QString &name);
	Object *createObjectFromJson(const QString &name, const QJsonObject &json);

	DataManager   *dataManager;
	PhysicsEngine *physics;
	SoundsManager *soundsManager;

	AnimatorManager *animatorManager;
	MapManager *mapManager;
	ItemConstructor *constructor;

	QVector<Object *> objects;
	QHash<const int, Object *> uidToObject;
	QHash<const int, Faction *> factions;
	QLinkedList<Effect> activeEffects;

	bool basePolygonsEffectOn;
};
