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
	bool lose = false;
	int fires = 0;
	int numFires = 0;
	// una idea para el final es hacer que si se pierde empiecen a flotar los bloques y salga un texto de que has perdido
	PxScene* scene;
	PxPhysics* physics;
	list<RigidBody*> rbs;
	list<RigidBody*> rbsToDelete;
	RigidBodyForceRegistry* rbRgis;
	BuoyancyForceGenerator* water = nullptr;
	list<Firework*> fireworks;
	list<Particle*> particles;
	void deleteUnusedRB();
public:
	bool win = false; // si fin es true entonces antes de empezar un nivel hay que borrar los fuegos artificiales o los muelles/flotabilidad
	Generator(PxScene* Scene, PxPhysics* Physics) :scene(Scene), physics(Physics) { rbRgis = new RigidBodyForceRegistry(); };
	virtual void update(float t);
	void shootRB();
	bool nivel1();
	bool nivel2();
	bool nivel3();
	void winGame();
	void borraWin();
	void Fireworks(float t);
	void gameOver();
	void borraFlot();

	void addWind() {
		WindForceGenerator* wind = new WindForceGenerator(Vector3(-60, 0, 0), 0.25, 0.1);
		for (auto rb : rbs)
			rbRgis->addRegistry(wind, rb);
	}

	void addFirework(Firework* f);
	void addParticle(Particle* p);
};

