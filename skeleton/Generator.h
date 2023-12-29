#pragma once
#include "core.hpp"
#include <list>
#include "RigidBody.h"
#include "RigidBodyForceRegistry.h"
#include "BouyancyForceGenerator.h"
#include "WindForceGenerator.h"
#include "FireWork.h"
#include "Particle.h"
using namespace std;
class Generator
{
protected:
	int numObstacles;
	bool playing = false;
	bool clic = false;
	int fires = 0;
	int numFires = 0;
	PxScene* scene;
	PxPhysics* physics;
	list<RigidBody*> rbs;
	list<RigidBody*> rbsToDelete;
	list<RigidBody*> shoots;
	list<RigidBody*> shootsToDelete;
	RigidBodyForceRegistry* rbRgis;
	BuoyancyForceGenerator* water = nullptr;
	list<Firework*> fireworks;
	list<Particle*> particles;
	void deleteUnusedRB();
public:
	bool win = false;
	bool lose = false;
	float cont = 0;
	Generator(PxScene* Scene, PxPhysics* Physics) :scene(Scene), physics(Physics), playing(false)
	{
		rbRgis = new RigidBodyForceRegistry(); 
	};
	virtual void update(float t);
	void shootRB();
	void shoot(Vector3 dir);
	bool nivel1();
	bool nivel2();
	bool nivel3();
	bool nivel4();
	void winGame();
	void borraWin();
	void Fireworks(float t);
	void gameOver();
	void borraFlot();

	void addWind() {
		WindForceGenerator* wind = new WindForceGenerator(Vector3(-60, 0, 0), 0.25, 0.1);
		for (auto rb : shoots)
			rbRgis->addRegistry(wind, rb);
	}

	void addFirework(Firework* f);
	void addParticle(Particle* p);
};

