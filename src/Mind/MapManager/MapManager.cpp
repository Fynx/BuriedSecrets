/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/MapManager/MapManager.hpp"

#include <QList>
#include <QRectF>

#include "Common/Strings.hpp"
#include "GameObjects/Unit.hpp"


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


bool MapManager::hasBeenSeen(const QPointF &point, const int factionId) const
{
	auto iter = FOWs.find(factionId);
	if (iter != FOWs.end()) {
		return iter.value().isVisible(point);
	}

	warn("MapManager: The point has not been seen, because the faction " +
			QString::fromStdString(std::to_string(factionId)) +
			" hasn't registered anything in MapManager yet!");
	return false;
}


bool MapManager::hasBeenSeen(const Object *object, const int factionId) const
{
	auto iter = FOWs.find(factionId);
	if (iter != FOWs.end()) {
		return ((const VisibilityMap *)&(iter.value()))->isVisible(nullptr, object, physicsEngine);
	}

	warn("MapManager: The point has not been seen, because the faction " +
			QString::fromStdString(std::to_string(factionId)) +
			" hasn't registered anything in MapManager yet!");
	return false;
}


bool MapManager::hasBeenSeen(const Object *object) const
{
	return hasBeenSeen(object, playerFactionId);
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


void MapManager::addVisibility(const Unit *unit, const BS::Geometry::Circle circle, const int factionId)
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
		if (!prot->hasProperty(Properties::Transparent) && unit->getLocation() != obj) {
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
			// ommitPolygon.append(centre);	// TODO uncomment when height is fixed.
			ommitPolygon.append(left);
			ommitPolygon.append(getPointOnCircleInline(circle, left));
			ommitPolygon.append(getPointOnCircleInline(circle, right));
			ommitPolygon.append(right);

			update.ommitPolygons.append(ommitPolygon);
		}
	}

	auto it = FOVs.find(factionId);
	if (it == FOVs.end()) {
		it = FOVs.insert(factionId, DiffVisibilityMap{});
	}
	it.value().update(update);

	if (factionId == playerFactionId) {
		visibilityUpdatesDiff->append(update);
	}

	// FOW
	auto iter = FOWs.find(factionId);
	if (iter == FOWs.end()) {
		iter = FOWs.insert(factionId, ImageVisibilityMap{map.getSize().toSize()});
	}
	iter.value().update(update);
}


VisibilityUpdateDiff *MapManager::getVisibilityUpdatesDiff()
{
	auto *ptr = visibilityUpdatesDiff;
	visibilityUpdatesDiff = new VisibilityUpdateDiff{};
	return ptr;
}


QPointF MapManager::getPointOnCircleInline(const BS::Geometry::Circle &circle, const QPointF &p)
{
	BS::Geometry::Line l{p, circle.centre};
	const float f = 2;	// The coefficient controlling how far the radius will reach.
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
