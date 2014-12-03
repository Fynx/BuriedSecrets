/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Box2DEngine.hpp"

Box2DEngine::Box2DEngine() : PhysicsEngine(), world(b2Vec2(0,0))
{

}


void Box2DEngine::addObject(Object *obj, QPointF pos)
{

}


void Box2DEngine::removeObject(Object *obj)
{

}


void Box2DEngine::updatePhysics(int msc)
{

}


void Box2DEngine::setPosition(Object *obj, QPointF pos)
{

}


void Box2DEngine::setVelocity(Object *obj, QVector2D v)
{

}


QPointF Box2DEngine::getPosition(Object *obj)
{
	return QPointF(0, 0);
}


Object *Box2DEngine::getFirstHit(QPointF position, QVector2D direction)
{
	return NULL;
}


QList<Object *> Box2DEngine::getColliding(Object *obj)
{
	QList<Object *> res;
	return res;
}


QList<Object *> Box2DEngine::testAABB(QRectF rect)
{
	QList<Object *> res;
	return res;
}
