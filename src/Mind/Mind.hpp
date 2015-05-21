/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QtCore>

#include "Common/Enums.hpp"
#include "GameObjects/Object.hpp"
#include "GameObjects/Faction.hpp"
#include "Mind/Effect.hpp"
#include "Mind/Event.hpp"

class AnimatorManager;
class DataManager;
class ItemConstructor;
class JournalEntry;
class Map;
class MapManager;
class PhysicsEngine;
class Quest;
class SoundsManager;

/**
 * @class Mind
 * Mind is a class that manages GameObjects and Animators.
 * Provides functions for load & save for GameObjects and MapManager.
 * Contains GameObjects access interface.
 */
class Mind : public QObject {
Q_OBJECT
public:
	static const int PlayerFactionId;

	Mind(DataManager *dataManager, PhysicsEngine *physicsEngine, SoundsManager *soundsManager);
	~Mind();

	PhysicsEngine *physicsEngine();
	ItemConstructor *itemConstructor();
	AnimatorManager *getAnimatorManager();

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
	void addObject(Object* object, const QPointF &position, float angle = 0);
	void addObject(Object* object);
	Object *createDefaultObject(BS::Type type, QString prototype);
	void removeObject(Object *object);

	bool isNotRemoved(int uid) const;
	Object *getObjectFromUid(const int uid);
	const Object *getObjectFromUid(const int uid) const;
	Faction *getFactionById(const int id);
	const Faction *getFactionById(const int id) const;
	Faction *getPlayerFaction();
	const Faction *getPlayerFaction() const;
	QVector<const Object *> getAllObjects() const;

	/** Convenience access functions for GameObjects. */
	Equipment *getEquipment(const int uid);
	Item *getItem(const int uid);
	Journal *getJournal(const int uid);
	JournalEntry *getJournalEntry(const int uid);
	Location *getLocation(const int uid);
	Quest *getQuest(const int uid);
	Unit *getUnit(const int uid);
	const Unit *getUnit(const int uid) const;

	JournalEntry *getEntryFromType(BS::EntryType type);

	/** Reaction to encounters with characters. */
	void acceptPendingUnit(int uid);
	void declinePendingUnit(int uid);

	/** Timeflow control. */
	void pauseGame();
	void resumeGame();

	/** General game state - won, lost or running. */
	BS::GameState getGameState() const;
	void setGameState(BS::GameState gameState);

	QLinkedList<Effect> * const getActiveEffects();
	QLinkedList<Effect>::iterator addEffect(const Effect &effect);
	/**
	 * @brief Deletes the effect from the list.
	 *
	 * Warning: This method invalidates (only) the passed iterator.
	 */
	void deleteEffect(QLinkedList<Effect>::iterator effectIterator);

	void toggleBasePolygons();
	void toggleShowPaths();

	int getSecsSinceBeginning() const;
	void incSecsSinceBeginning();

private:
	Object *createObject(BS::Type type, const QString &name);
	Object *createObjectFromJson(const QString &name, const QJsonObject &json);
	void removeAllEffects(const QString &name);

	DataManager   *dataManager;
	PhysicsEngine *physics;
	SoundsManager *soundsManager;

	AnimatorManager *animatorManager;
	MapManager *mapManager;
	ItemConstructor *constructor;

	BS::GameState gameState;
	QVector<Object *> objects;
	QHash<const int, Object *> uidToObject;
	QHash<const int, Faction *> factions;
	QHash<BS::EntryType, JournalEntry *> entries;
	QLinkedList<Effect> activeEffects;

	bool basePolygonsEffectOn;
	bool showPathsEffectOn;

	int secsSinceBeginning;
};
