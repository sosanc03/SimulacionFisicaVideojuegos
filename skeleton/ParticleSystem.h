#pragma once
#include <list>
#include "Particle.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "VortexForceGenerator.h"
#include "BurstForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
using namespace std;

class ParticleSystem
{
public:enum SpringType{SPRING, ANCHORED, FLOTABILITY, GOMAELASTICA, NONE};
private:
	ParticleForceRegistry* partRgis;
	list<Particle*> particles;
	list<Firework*> fireworks;
	//list<SpringForceGenerator*> springs;

public:
	ParticleSystem() { partRgis = new ParticleForceRegistry();  }
	~ParticleSystem();
	void update(float t);
	void addParticle(Particle* p);
	void addFirework(Firework* f);
	void addExplosion();
	void generateSpringDemo(SpringType type);
	void addK(int k);
protected:
	void addGravity(Particle* p);
	void addWind(Particle* p);
	void addVortex(Particle* p);
	void addBurst(Particle* p);
	
};

