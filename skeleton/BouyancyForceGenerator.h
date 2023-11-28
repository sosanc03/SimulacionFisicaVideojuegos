#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator {
protected:
	float height, volume, lDensity, gravity = 9.8;
	Particle* liquidParticle;

public:
	BuoyancyForceGenerator(float Height, float Volume, float Density) :height(Height), volume(Volume), lDensity(Density) {};
	~BuoyancyForceGenerator() {};

	virtual void updateForce(Particle* particle);
};

