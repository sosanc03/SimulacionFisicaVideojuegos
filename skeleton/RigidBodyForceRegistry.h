#pragma once
#include <map>
#include "RigidBody.h"
#include "ForceGenerator.h"

using namespace std;

class RigidBodyForceRegistry {
private:
	multimap<ForceGenerator*, RigidBody*> registry;

public:
	RigidBodyForceRegistry();
	~RigidBodyForceRegistry();
	void clear();
	void addRegistry(ForceGenerator* f, RigidBody* rb);
	void deleteRigidBodyRegistry(RigidBody* rb);
	void deleteForceRegistry(ForceGenerator* f);
	void updateForces(double t);
	multimap<ForceGenerator*, RigidBody*> const& getRegistry() { return registry; }
};