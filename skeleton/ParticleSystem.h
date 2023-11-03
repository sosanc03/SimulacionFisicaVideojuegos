#pragma once
#include <list>
#include "Particle.h"
#include "Firework.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
using namespace std;

class ParticleSystem
{
private:
	ParticleForceRegistry* partRgis;
	list<Particle*> particles;
	list<Firework*> fireworks;

public:
	ParticleSystem() { partRgis = new ParticleForceRegistry(); }
	~ParticleSystem();
	void update(float t);
	void addParticle(Particle* p);
	void addFirework(Firework* f);
	void addGravity(Particle* p);
};

