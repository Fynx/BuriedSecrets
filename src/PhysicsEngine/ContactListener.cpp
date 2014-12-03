#include "ContactListener.hpp"


ContactListener::ContactListener()
{

}


void ContactListener::BeginContact(b2Contact *contact)
{
	Object *firstGo = static_cast<Object *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Object *secondGo = static_cast<Object *>(contact->GetFixtureB()->GetBody()->GetUserData());

	if ( firstGo && secondGo ){
		collisions[firstGo].insert(secondGo);
		collisions[secondGo].insert(firstGo);
	}
}


void ContactListener::EndContact(b2Contact *contact)
{
	Object *firstGo = static_cast<Object *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Object *secondGo = static_cast<Object *>(contact->GetFixtureB()->GetBody()->GetUserData());

	if ( firstGo && secondGo ){
		collisions[firstGo].remove(secondGo);
		collisions[secondGo].remove(firstGo);
	}
}
