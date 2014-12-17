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
	  physics(physicsEngine),
	  soundsManager(soundsManager),
	  animatorManager(new AnimatorManager(this))
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

void Mind::newGameActivated()
{
	qDebug() << "Let the game begin!";
	//TODO
}

void Mind::addObject(Object *object, const QPointF &position)
{
	objects.append(object);
	uidToObject[object->getUid()] = object;
	physics->addObject(object, position);
}

Object *Mind::getObjectFromUid(const int uid)
{
	if (uidToObject.contains(uid))
		return uidToObject[uid];
	else
		qDebug() << "Mind::getObjectFromUid: uid not found";
	return nullptr;
}

PhysicsEngine *Mind::physicsEngine()
{
	return physics;
}

void Mind::insertMap(const Map *map)
{
	qDebug() << "Inserting map...";
	for (const Map::Object &object : map->getObjects()) {
		Object *obj;
		if (object.properties["type"] == "building") {
			Building *building = new Building(dataManager->getPrototype("building"));
			obj = building;
		}
		QPointF coordinates = {object.properties["x"].toFloat(), object.properties["y"].toFloat()};
		addObject(obj, coordinates);
	}

	//TODO !!! connect with animators
}

QDataStream &operator<<(QDataStream &out, const Mind &mind)
{
	qDebug() << "Saving dataObjects...";

	out << static_cast<qint32>(mind.objects.size());
	for (const Object *obj : mind.objects) {
		qDebug() << "\tsave" << obj->getUid();
		out << QString("building") << *obj << mind.physics->getPosition(obj);
	}

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
			Building *building = new Building(mind.dataManager->getPrototype("building"));
			qDebug() << "\tbuilding" << building->getUid();
			QPointF pos;
			in >> *building;
			in >> pos;
			mind.addObject(building, pos);

			// ----- Cut here ----- //
			if (i == 0) {
				mind.animatorManager->addObject("Test", building);
			}

			mind.animatorManager->addObject("Animations", building);

			// ----- Cut here ----- //
		} else {
			qDebug() << "Object other than a building! O.O";
		}
	}

	qDebug() << "done.";

	return in;
}
