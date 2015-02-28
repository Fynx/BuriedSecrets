/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/MapManager/MapManager.hpp"

#include <QList>
#include <QRectF>

#include "Common/Strings.hpp"


MapManager::MapManager(const QJsonObject &json, const PhysicsEngine *physicsEngine, const int playerFactionId)
	: playerFactionId{playerFactionId}, map{json}, physicsEngine{physicsEngine},
	visibilityUpdatesDiff{new VisibilityUpdateDiff{}}
{}


const Map *MapManager::getMap() const
{
	return &map;
}


QList<QPointF> MapManager::getPath(const QPointF &from, const QPointF &to) const
{
	QList<QPointF> result{to};

	// TODO

	return result;
}


QList<const Object *> MapManager::getVisibleObjects(const Unit *unit) const
{
	QList<const Object *> result;
	float radius = unit->getSightRange();
	QPointF radiusP{radius, radius};
	QPointF pos = physicsEngine->getPosition(unit);
	auto objects = physicsEngine->getObjectsInRect(QRectF{pos - radiusP, pos + radiusP});

	//VisibilityUpdate FOV = getUnitFOV(unit);

	for (const Object *obj: objects) {
		//if (obj != unit && canBeSeen(obj, FOV)) {
			result.append(obj);
		//}
	}

	return result;
}


void MapManager::clearFieldOfView(const int factionId)
{
	FOVs[factionId].clear();
}


void MapManager::addVisibility(const BS::Geometry::Circle circle, const int factionId)
{
	// FOV
	VisibilityUpdate update;
	update.includeCircle = circle;
	// Exclude potentially invisible regions.
	// Get all objects potentially in circle.
	QRectF boundingRect = QRectF{circle.centre.x() - circle.radius, circle.centre.y() - circle.radius,
		circle.radius * 2.0f, circle.radius * 2};
	auto objects = physicsEngine->getObjectsInRect(boundingRect);
	for (const Object *obj: objects) {
		const Prototype *prot = obj->getPrototype();
		QPointF pos = physicsEngine->getPosition(obj);
		QPointF baseCentre;
		QPointF centre;
		QPointF left, right;
		if (prot->hasProperty("baseRadius")) {
			// It's an object with a circular base.
			// TODO FIXME not doing it now, because of lack of time to do the math.
			// If we want this in the future, here's where we'd implement it.
			continue;	//Not supported.
		} else if (prot->hasProperty("basePolygon")) {
			baseCentre = prot->getBaseCentre();
			left = right = centre = pos;
			const auto basePolygon = prot->getBasePolygon();

			for (QPointF p: basePolygon) {
				p += pos - baseCentre;
				if (BS::Geometry::toLeft(circle.centre, left, p)) {
					left = p;
				} else if (!BS::Geometry::toLeft(circle.centre, right, p)) {
					right = p;
				}
			}
		} else {
			warn("MapManager: Object '" + obj->getName() +
					"' does not have baseRadius nor basePolygon. Skipping");
			continue;
		}

		BS::Geometry::Polygon ommitPolygon;
		ommitPolygon.append(centre);
		ommitPolygon.append(left);
		ommitPolygon.append(getPointOnCircleInline(circle, left));
		ommitPolygon.append(getPointOnCircleInline(circle, right));
		ommitPolygon.append(right);

		update.ommitPolygons.append(ommitPolygon);
	}

	FOVs[factionId].append(update);
	if (factionId == playerFactionId) {
		visibilityUpdatesDiff->append(update);
	}
	// TODO FOW
}


MapManager::VisibilityUpdateDiff * MapManager::getVisibilityUpdatesDiff()
{
	auto *ptr = visibilityUpdatesDiff;
	visibilityUpdatesDiff = new VisibilityUpdateDiff{};
	return ptr;
}


QPointF MapManager::getPointOnCircleInline(const BS::Geometry::Circle &circle, const QPointF &p)
{
	BS::Geometry::Line l{p, circle.centre};
	const float f = 1.2;	// The coefficient controlling how far the radius will reach.
	float a = l.A * l.A + l.B * l.B;
	float b = -2.0f * l.B * l.B * circle.centre.x() + 2.0f * l.A * l.B * circle.centre.y() + 2.0f * l.A * l.C;
	float c = l.B * l.B * circle.centre.x() * circle.centre.x() +
			l.B * l.B * circle.centre.y() * circle.centre.y() + 2.0f * l.B * l.C * circle.centre.y() +
			l.C * l.C - f * f * l.B * l.B * circle.radius * circle.radius;
	float delta = b * b - 4.0f * a * c;
	delta = sqrt(delta);
	float xOne = (-b - delta) / 2.0f / a;
	float xTwo = (-b + delta) / 2.0f / a;
	QPointF resOne{xOne, l.getY(xOne)};
	QPointF resTwo{xTwo, l.getY(xTwo)};

	return (BS::Geometry::distance(resOne, p) < BS::Geometry::distance(resTwo, p)) ? resOne : resTwo;
}


VisibilityUpdate MapManager::getUnitFOV(const Unit *unit) const
{
	float radius = unit->getSightRange();
	QPointF pos = physicsEngine->getPosition(unit);
	Q_ASSERT(FOVs.contains(unit->getFactionId()));
	const auto &FOV = FOVs[unit->getFactionId()];

	// Find the entry for the unit.
	for (const auto &entry: FOV) {
		if (entry.includeCircle.centre == pos && entry.includeCircle.radius == radius) {
			return entry;
		}
	}

	err("Visibility for the unit '" + unit->getName() +
			"' not found! Are you sure it has AnimatorUpdateFOV turned on?");
	Q_ASSERT(false);	// FOV for the unit not found.
	return VisibilityUpdate{};
}


bool MapManager::canBeSeen(const Object *object, const VisibilityUpdate &FOV) const
{
	const Prototype *prot = object->getPrototype();
	QPointF pos = physicsEngine->getPosition(object);
	const int pointsPerMetre = 3;

	if (prot->hasProperty(Properties::BaseRadius)) {
		// Check a constant (per metre of length) number of points on the circle.
		float radius = prot->getProperty(Properties::BaseRadius).toFloat();
		BS::Geometry::Circle circle{pos, radius};
		int pointsCount = circle.getLength() * pointsPerMetre;
		QPointF pointDiff{0.0f, radius};
		QTransform transform;
		transform.rotate(360.0f / pointsCount);

		while (pointsCount--) {
			if (canBeSeen(circle.centre + pointDiff, object, FOV)) {
				return true;
			}

			pointDiff = pointDiff * transform;
		}
	} else if (prot->hasProperty(Properties::BasePolygon)) {
		const auto basePolygon = prot->getBasePolygon();
		for (int i = 0; i < basePolygon.length(); ++i) {
			int j = (i + 1) % basePolygon.length();
			int pointsCount = BS::Geometry::distance(basePolygon.at(i), basePolygon.at(j)) * pointsPerMetre;
			QPointF pointDiff = (basePolygon.at(j) - basePolygon.at(i)) / pointsCount;
			QPointF point = basePolygon.at(i);

			while (pointsCount--) {
				if (canBeSeen(point, object, FOV)) {
					return true;
				}

				point += pointDiff;
			}
		}
	}

	return canBeSeen(pos, object, FOV);
}


bool MapManager::canBeSeen(const QPointF &point, const Object *target, const VisibilityUpdate &FOV) const
{
	// There are two approaches possible here:
	//  - use FOV data,
	//  - use raytracing from physics.
	// For now we'll stick to the second one and see how it works.

	return physicsEngine->getFirstHit(FOV.includeCircle.centre, QVector2D{point - FOV.includeCircle.centre},
					  FOV.includeCircle.radius) == target;
}


