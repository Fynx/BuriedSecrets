#pragma once

#include "DataManager/DataManager.hpp"
#include "GameObjects/Object.hpp"
#include "Mind/AnimatorManager.hpp"
#include "Mind/Event.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "SoundsManager/SoundsManager.hpp"

#include <QtCore>

class Mind : public QObject {

Q_OBJECT;
public:
	Mind(DataManager *dataManager, PhysicsEngine *physicsEngine, SoundsManager *soundsManager);
	~Mind();

private:
	DataManager   *dataManager;
	PhysicsEngine *physicsEngine;
	SoundsManager *soundsManager;

	AnimatorManager *animatorManager;

	QVector <Object *> objects;

	friend QDataStream &operator<<(QDataStream &out, const Mind &mind);
	friend QDataStream &operator>>(QDataStream &in, Mind &mind);
};
