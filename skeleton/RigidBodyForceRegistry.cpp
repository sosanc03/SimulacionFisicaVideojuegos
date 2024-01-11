#include "RigidBodyForceRegistry.h"

RigidBodyForceRegistry::RigidBodyForceRegistry() {

}

RigidBodyForceRegistry::~RigidBodyForceRegistry() {
	clear();
}

void RigidBodyForceRegistry::clear() {
	registry.clear();
}

void RigidBodyForceRegistry::addRegistry(ForceGenerator* f, RigidBody* rb) {
	registry.insert({ f, rb });
}

void RigidBodyForceRegistry::deleteRigidBodyRegistry(RigidBody* rb) {
	for (auto it = registry.begin(); it != registry.end(); ) {
		if (it->second == rb) { it = registry.erase(it); }
		else { it++; }
	}
}

void RigidBodyForceRegistry::deleteForceRegistry(ForceGenerator* f) {
	for (auto it = registry.begin(); it != registry.end(); ) {
		if (it->first == f) { it = registry.erase(it); }
		else { it++; }
	}
}

void RigidBodyForceRegistry::updateForces(double t) {
	for (auto fp : registry) {
		fp.first->updateForce(fp.second, t);
	}
}