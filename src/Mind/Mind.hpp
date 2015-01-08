/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore>

#include "DataManager/DataManager.hpp"
#include "DataManager/MapInfo.hpp"
#include "GameObjects/Object.hpp"
#include "GameObjects/Faction.hpp"
#include "Mind/AnimatorManager.hpp"
#include "Mind/Event.hpp"
#include "MapManager/MapManager.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "SoundsManager/SoundsManager.hpp"


class Mind : public QObject {

Q_OBJECT
public:
	Mind(DataManager *dataManager, PhysicsEngine *physicsEngine, SoundsManager *soundsManager);
	~Mind();

	PhysicsEngine *physicsEngine();

	void loadFromJson(const QJsonObject &json);
	QJsonObject saveToJson() const;

	const Map *getMap() const;

	/**
	 * @brief Adds an object to the inner collection and to physics.
	 *
	 * @param object The object to add.
	 * @param position The position at which it should initially be (physics).
	 * @return void
	 */
	void addObject(Object* object, const QPointF &position);
	void removeObject(Object *object);
	Object *getObjectFromUid(const int uid);
	Faction *getFactionFromUid(const int uid);

private:
	Object *createObject(BS::Type type, const QString &name);
	Object *createObjectFromJson(const QString &name, const QJsonObject &json);

	DataManager   *dataManager;
	PhysicsEngine *physics;
	SoundsManager *soundsManager;

	AnimatorManager *animatorManager;
	MapManager *mapManager;

	QVector<Object *> objects;
	QHash<const int, Object *> uidToObject;
	QHash<const int, Faction *> factions;
};
