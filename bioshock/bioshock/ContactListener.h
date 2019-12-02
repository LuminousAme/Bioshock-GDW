#pragma once

#include "PhysicsSystem.h"
#include <vector>
#include <algorithm>

struct MyContact {
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
	bool operator==(const MyContact& other) const
	{
		return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
	}
};

class MyContactListener : public b2ContactListener
{
public:
	std::vector<MyContact>_contacts;

	MyContactListener()
		: _contacts()
	{	}

	~MyContactListener() {

	}

	void BeginContact(b2Contact* contact)
	{
		MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() }; 
		_contacts.push_back(myContact);
	}

	void EndContact(b2Contact* contact)
	{
		MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() }; 
		std::vector<MyContact>::iterator pos;
		pos = std::find(_contacts.begin(), _contacts.end(), myContact);
		if (pos != _contacts.end())
		{
			_contacts.erase(pos);
		}
	}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
	}

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
	}
};