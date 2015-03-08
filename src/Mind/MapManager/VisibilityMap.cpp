/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/MapManager/VisibilityMap.hpp"

#include <QPointF>
#include <QTransform>

#include "Common/Geometry.hpp"
#include "Common/Strings.hpp"
#include "DataManager/Prototype.hpp"
#include "GameObjects/Object.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"


bool VisibilityMap::isVisible(const Unit *from, const Object *target, const PhysicsEngine *physicsEngine) const
{
	const Prototype *prot = target->getPrototype();
	QPointF pos = physicsEngine->getPosition(target);
	const float pointsPerMetre = 2.5;

	if (prot->hasProperty(Properties::BaseRadius)) {
		// Check a constant (per metre of length) number of points on the circle.
		float radius = prot->getProperty(Properties::BaseRadius).toFloat();
		BS::Geometry::Circle circle{pos, radius};
		int pointsCount = circle.getLength() * pointsPerMetre;
		QPointF pointDiff{0.0f, radius};
		QTransform transform;
		transform.rotate(360.0f / pointsCount);

		while (pointsCount--) {
			if (isVisible(from, circle.centre + pointDiff, target, physicsEngine)) {
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
			QPointF point = pos - prot->getBaseCentre() + basePolygon.at(i);

			while (pointsCount--) {
				if (isVisible(from, point, target, physicsEngine)) {
					return true;
				}

				point += pointDiff;
			}
		}
	}

	return isVisible(from, pos, target, physicsEngine);
}
