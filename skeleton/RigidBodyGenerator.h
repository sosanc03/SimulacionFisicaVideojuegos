#pragma once
#include <list>
#include <random>
#include <iostream>
#include "RigidBody.h"

using namespace std;

class RigidBodyGenerator {
private:
	PxScene* scene;
	PxPhysics* physics;

	int nGen;
	Vector3 pos, vel;
	RigidBody* rb_;
	float var = 2, median = 0;

	float frecuency;
	float timeNxtGen;

	bool active = true;

public:
	RigidBodyGenerator(PxScene* Scene, PxPhysics* Physics, RigidBody* rb, Vector3 position, Vector3 Vel = Vector3(0, 0, 0), int numGen = 1, float Frecuency = 0.2) :
		scene(Scene), physics(Physics), rb_(rb), pos(position), vel(Vel), nGen(numGen), frecuency(Frecuency), timeNxtGen(Frecuency), active(true) {
	};
	void update(float t);
	list<RigidBody*> generateBodies();
};