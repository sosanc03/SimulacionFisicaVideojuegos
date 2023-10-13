#pragma once
#include <list>
#include "particle.h"
#include "Firework.h"
using namespace std;

class ParticleSystem
{
private:
	list<Particle*> particles;
	list<Firework*> fireworks;

public:
	ParticleSystem();
	~ParticleSystem();
	void update(float t);
	void FireUpdate(float t);
	void PartUpdate(float t);
	void addParticle(Particle* p);
	void addFirework(Firework* f);
};

