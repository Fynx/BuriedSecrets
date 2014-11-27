#include "Mind/Mind.hpp"
#include "GameObjects/Building.hpp"
#include "GameObjects/Fortification.hpp"

//TODO use DebugManager instead
#include <QtCore>


Mind::Mind(DataManager *dataManager, PhysicsEngine *physicsEngine, SoundsManager *soundsManager)
	: dataManager(dataManager),
	  physicsEngine(physicsEngine),
	  soundsManager(soundsManager),
	  animatorManager(new AnimatorManager)
{
	qDebug() << "Mind initialized. Triggering destruction of the world.";
	soundsManager->onEvent(QString("No events for you!"));

	// FIXME A temporary game objects:
	Building *obj1 = new Building(&prototype);
	Building *obj2 = new Building(&prototype);
	obj1->setPosition(0, 0);
	obj2->setPosition(20, 30);

	objects.append(obj1);
	objects.append(obj2);
}


Mind::~Mind()
{
	delete animatorManager;
	qDeleteAll(objects);
}


QVector<Object *> Mind::getObjectsInRect(const QRect& rect) const
{
	QVector<Object *> res;
	// FIXME TODO
	return objects;
}


QDataStream &operator<<(QDataStream &out, const Mind &mind)
{
	qDebug() << "saving dataObjects";
	return out;
}


QDataStream &operator>>(QDataStream &in, Mind &mind)
{
	qDebug() << "loading dataObjects";
	Fortification *itsATrap = new Fortification(mind.dataManager->getPrototype("ItsATrap"));
	mind.objects.append(itsATrap);
	return in;
}
