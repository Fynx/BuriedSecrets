/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Mind.hpp"

#include "Common/Strings.hpp"
#include "GameObjects/Building.hpp"
#include "GameObjects/Camp.hpp"
#include "GameObjects/Equipment.hpp"
#include "GameObjects/Fortification.hpp"
#include "GameObjects/Mob.hpp"
#include "GameObjects/Unit.hpp"

//TODO use DebugManager instead
#include <QtCore>


Mind::Mind(DataManager *dataManager, PhysicsEngine *physicsEngine, SoundsManager *soundsManager)
	: dataManager(dataManager),
	  physics(physicsEngine),
	  soundsManager(soundsManager),
	  animatorManager(new AnimatorManager(this)),
	  mapManager(nullptr)
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
	delete mapManager;
	qDeleteAll(objects);
}

void Mind::addObject(Object *object, const QPointF &position)
{
	qDebug() << "addObject:" << object->getUid();
	objects.append(object);
	uidToObject[object->getUid()] = object;
	physics->addObject(object, position);
}

void Mind::removeObject(Object *object)
{
	qDebug() << "removeObject:" << object->getUid();
	objects.removeAll(object);
	uidToObject.remove(object->getUid());
	physics->removeObject(object);
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

void Mind::insertMap(const MapInfo *map)
{
	qDebug() << "Inserting map...";

	delete mapManager;
	mapManager = new MapManager(map);

	for (const MapInfo::Object &object : map->getObjects()) {
		qDebug() << "\tinsert object: type=" << object.properties["type"].toString()
			<< "name=" << object.properties["name"].toString();

		BS::Type type = BS::changeStringToType(object.properties["type"].toString());
		Object *obj = createObject(type, object.name);

		for (const QVariant &value : object.properties["animators"].toList())
			if (!animatorManager->addObject(value.toString(), obj))
				qDebug() << "\t\tfailed to add animator" << value.toString();

		QPointF coordinates = {object.properties["x"].toFloat(), object.properties["y"].toFloat()};
		addObject(obj, coordinates);
	}
}

const Map *Mind::getMap() const
{
	return mapManager->getMap();
}

QDataStream &operator<<(QDataStream &out, const Mind &mind)
{
	qDebug() << "Saving dataObjects...";

	out << static_cast<qint32>(mind.objects.size());
	for (const Object *obj : mind.objects) {
		qDebug() << "\tsave" << obj->getUid();
		out << BS::changeTypeToString(obj->getType()) << obj->getName() << obj->getUid()
			<< *obj << mind.physics->getPosition(obj) << mind.animatorManager->getAnimatorsForObject(obj);
		qDebug() << "\t\t" << BS::changeTypeToString(obj->getType()) << obj->getName()
			<< mind.physics->getPosition(obj) << mind.animatorManager->getAnimatorsForObject(obj);
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
		QString typeString;
		QString name;
		int uid;
		in >> typeString >> name >> uid;
		BS::Type type = BS::changeStringToType(typeString);

		qDebug() << "\t" << typeString << name;

		Object *object = mind.createObject(type, name);
		in >> *object;

		QPointF pos;
		in >> pos;
		qDebug() << "\t\t" << pos;
		mind.addObject(object, pos);

		QVector<QString> animators;
		in >> animators;
		qDebug() << "\t\tanimators:" << animators;
		for (const QString &animator : animators)
			mind.animatorManager->addObject(animator, object);
	}

	qDebug() << "done.";

	return in;
}

Object *Mind::createObject(BS::Type type, const QString &name)
{
	Object *obj;
	switch (type) {
		case BS::Type::Invalid: {
			qDebug() << "Explosion: Invalid object type";
			break;
		}
		case BS::Type::Building: {
			Building *building = new Building(dataManager->getPrototype(name));
			obj = building;
			break;
		}
		case BS::Type::Camp: {
			Camp *camp = new Camp(dataManager->getPrototype(name));
			obj = camp;
			break;
		}
		case BS::Type::Equipment: {
			Equipment *equipment = new Equipment(dataManager->getPrototype(name));
			obj = equipment;
			break;
		}
		case BS::Type::Fortification: {
			Fortification *fortification = new Fortification(dataManager->getPrototype(name));
			obj = fortification;
			break;
		}
		case BS::Type::Mob: {
			Mob *mob = new Mob(dataManager->getPrototype(name));
			obj = mob;
			break;
		}
		case BS::Type::Unit: {
			Unit *unit = new Unit(dataManager->getPrototype(name));
			obj = unit;

			// ----- Cut here ----- //
			QList<QPointF> tmpPath;
			tmpPath.append(QPointF(50, 5));
			tmpPath.append(QPointF(5, 50));
			tmpPath.append(QPointF(5, 10));
			tmpPath.append(QPointF(30, 50));
			tmpPath.append(QPointF(50, 25));
			tmpPath.append(QPointF(5, 5));
			unit->setCurrentPath(tmpPath);
			// ----- Cut here ----- //

			break;
		}
		default: {
			qDebug() << "blablabla...\n" << "blabla?";
		}
	}

	return obj;
}
