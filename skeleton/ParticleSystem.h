#pragma once
#include <list>
#include "Particle.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "VortexForceGenerator.h"
#include "BurstForceGenerator.h"
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
	void addExplosion();
protected:
	void addGravity(Particle* p);
	void addWind(Particle* p);
	void addVortex(Particle* p);
	void addBurst(Particle* p);
	
};

