/* YoLoDevelopment, 2014
 * All rights reserved.
 */
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
	qDebug() << "Mind initialized. Select 'Load mind' from the menu options to load objects.";
	qDebug() << "Or add loadFromFile(\"data/map.bin\") here in Mind::Mind.";
	qDebug() << "You can even add saveFromFile here.";
	qDebug() << "SoundsManager event test.";
	soundsManager->onEvent(QString("test: success"));
}

Mind::~Mind()
{
	delete animatorManager;
	qDeleteAll(objects);
}

QVector<Object *> Mind::getObjectsInRect(const QRect &rect) const
{
	QVector <Object *> res;
	// FIXME TODO
	return objects;
}

QDataStream &operator<<(QDataStream &out, const Mind &mind)
{
	qDebug() << "Saving dataObjects...";

	qint32 dataObjectsNumber = 2;
	out << dataObjectsNumber;

	// FIXME Temporary game objects:
	Building obj1(mind.dataManager->getPrototype("building"));
	Building obj2(mind.dataManager->getPrototype("building"));
	obj1.setPosition(0, 0);
	obj2.setPosition(20, 30);

	out << QString("building") << obj1;
	out << QString("building") << obj2;

	qDebug() << "done.";

	return out;
}

QDataStream &operator>>(QDataStream &in, Mind &mind)
{
	qDebug() << "Loading dataObjects...";

	qint32 dataObjectsNumber;
	in >> dataObjectsNumber;

	for (int i = 0; i < dataObjectsNumber; ++i) {
		QString type;
		in >> type;

		if (type == "building") {
			qDebug() << "\tbuilding";
			Building *building = new Building(mind.dataManager->getPrototype("building"));
			in >> *building;
			mind.objects.append(building);
		} else {
			qDebug() << "Object other than a building! O.O";
		}
	}

	qDebug() << "done.";

	return in;
}
