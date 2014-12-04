#include "AABBCallback.hpp"


AABBCallback::AABBCallback()
{

}


bool AABBCallback::ReportFixture(b2Fixture *fixture)
{
	Object *obj = static_cast<Object *>(fixture->GetBody()->GetUserData());
	if (!obj)
		return true;

	foundObjects.push_back(obj);
	return true;
}
