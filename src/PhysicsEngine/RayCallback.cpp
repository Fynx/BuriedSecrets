#include "RayCallback.hpp"


RayCallback::RayCallback() : nearestFraction(1000000), obj(NULL)
{
}


float32 RayCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction)
{
	if (fraction < nearestFraction)
		obj = static_cast<Object *> (fixture->GetBody()->GetUserData());
	return fraction;
}
