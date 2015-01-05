/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Box2DEngine.hpp"
#include "AABBCallback.hpp"
#include "RayCallback.hpp"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Box2DEngine::Box2DEngine() : PhysicsEngine(), world(b2Vec2(0,0)), listener()
{
	world.SetContactListener(&listener);
}


void Box2DEngine::addObject(Object *obj, const QPointF &pos, const float angle)
{
	/*
	 * All the stuff from Objects' Prototypes
	 */
	b2BodyDef bodyDef;

	b2Shape *shape;
	const auto objType = obj->getPrototype()->getProperty("type").toString();
	if (objType == "unit") {
		shape = new b2CircleShape();
		dynamic_cast<b2CircleShape *>(shape)->m_radius =
				obj->getPrototype()->getProperty("baseRadius").toFloat();
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(
			pos.x() - ((b2CircleShape*) shape)->m_radius, pos.y() - ((b2CircleShape*) shape)->m_radius);
	} else {
		// We assume building
		shape = new b2PolygonShape();
		// Take the base polygon.
		QVariantList verts = obj->getPrototype()->getProperty("basePolygon").toList();
		b2Vec2 vertices[verts.size()];
		float minX = verts[0].toList()[0].toFloat();
		float minY = verts[0].toList()[1].toFloat();
		float centreX = 0.f;
		float centreY = 0.f;
		// Calculate minX, minY and the centre of mass (as if the shape was aligned to the upper left corner
		// as much as possible).
		for (const QVariant &point: verts) {
			const QVariantList p = point.toList();
			minX = std::min(minX, p[0].toFloat());
			minY = std::min(minY, p[0].toFloat());
			centreX += p[0].toFloat();
			centreY += p[1].toFloat();
		}

		centreX -= minX * verts.size();
		centreY -= minY * verts.size();

		centreX /= verts.size();
		centreY /= verts.size();

		// Add the vertices to Box2D
		for (int i = 0; i < verts.size(); ++i) {
			// Align the polygon to the upper left corner and then move it so that (0, 0) is at the centre
			// of mass.
			vertices[i].Set(verts[i].toList()[0].toFloat() - minX - centreX,
					verts[i].toList()[1].toFloat() - minY - centreY);
		}
		dynamic_cast<b2PolygonShape *>(shape)->Set(vertices, verts.size());
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(pos.x(), pos.y());
	}
	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape;
	fixtureDef.density = 10.0f; //?
	fixtureDef.friction = 10.f; //?

	b2Body* body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	body->SetUserData(obj);

	objects.insert(obj, body);
}


void Box2DEngine::removeObject(Object *obj)
{
	if (!obj)
		return;
	if (objects.count(obj) == 0)
		return;
	world.DestroyBody(objects.value(obj));
	objects.remove(obj);
	listener.collisions.remove(obj);
}


void Box2DEngine::updatePhysics(const int msc)
{
	float32 timeStep = msc / 1000.0;
	world.Step(timeStep, VELOCITY_ITS, POSITION_ITS);
}


void Box2DEngine::setAngle(Object *obj, float angle)
{
	b2Body *body = objects.value(obj);
	if (!body)
		return;

	if (angle >= 360. || angle < 0)
		angle = body->GetAngle() * RADTODEG;

	angle = angle * DEGTORAD;

	body->SetTransform(body->GetPosition(), angle);
}


void Box2DEngine::setPosition(Object *obj, const QPointF &pos, float angle)
{
	b2Body *body = objects.value(obj);
	if (!body)
		return;

	if (angle >= 360. || angle < 0)
		angle = body->GetAngle() * RADTODEG;

	angle = angle * DEGTORAD;
	body->SetTransform(b2Vec2(pos.x(), pos.y()), angle);
}


void Box2DEngine::setVelocity(Object *obj, const QVector2D &v)
{
	b2Body *body = objects.value(obj);
	if (!body)
		return;
	body->SetLinearVelocity(b2Vec2(v.x(), v.y()));
}


const QPointF Box2DEngine::getPosition(const Object *obj) const
{
	b2Body *body = objects.value(obj);
	if (!body)
		return QPointF(0, 0);

	return QPointF(body->GetPosition().x, body->GetPosition().y);
}


const float Box2DEngine::getAngle(const Object *obj) const
{
	b2Body *body = objects.value(obj);
	assert(body);

	return body->GetAngle() * RADTODEG;
}


Object *Box2DEngine::getFirstHit(const QPointF &position, QVector2D direction, const float range) const
{
	direction.normalize();
	QPointF dest = position + (direction *range).toPointF();
	RayCallback callback;

	world.RayCast(&callback, b2Vec2(position.x(), position.y()), b2Vec2(dest.x(), dest.y()));

	return nullptr;
}


const QList<const Object *> Box2DEngine::getColliding(const Object *obj) const
{
	QList<const Object *> res = listener.collisions.value(obj).toList();
	return res;
}


const QList< const Object * > Box2DEngine::getObjectsInRect(const QRectF &rect) const
{
	AABBCallback queryCallback;
	b2AABB query;
	query.lowerBound.x = rect.left();
	query.lowerBound.y = rect.top();
	query.upperBound.x = rect.right();
	query.upperBound.y = rect.bottom();
	world.QueryAABB(&queryCallback, query);

	return queryCallback.foundObjects;
}
