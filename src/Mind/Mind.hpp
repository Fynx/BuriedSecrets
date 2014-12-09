/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore>

#include "DataManager/DataManager.hpp"
#include "GameObjects/Object.hpp"
#include "Mind/AnimatorManager.hpp"
#include "Mind/Event.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "SoundsManager/SoundsManager.hpp"


class Mind : public QObject {

Q_OBJECT;
public:
	Mind(DataManager *dataManager, PhysicsEngine *physicsEngine, SoundsManager *soundsManager);
	~Mind();

	// it may also be a slot
	void newGameActivated();
	PhysicsEngine *physicsEngine();

private:
	/**
	 * @brief Adds an object to the inner collection and to physics.
	 *
	 * @param object The object to add.
	 * @param position The position at which it should initially be (physics).
	 * @return void
	 */
	void addObject(Object* object, const QPointF &position);

	DataManager   *dataManager;
	PhysicsEngine *physics;
	SoundsManager *soundsManager;

	AnimatorManager *animatorManager;

	QVector <Object *> objects;

	friend QDataStream &operator<<(QDataStream &out, const Mind &mind);
	friend QDataStream &operator>>(QDataStream &in, Mind &mind);
};
