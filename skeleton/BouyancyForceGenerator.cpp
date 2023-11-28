#include "BouyancyForceGenerator.h"

void BuoyancyForceGenerator::updateForce(Particle* particle) {
	float h = particle->getTransform()->p.y;
	float h0 = liquidParticle->getTransform()->p.y;

	Vector3 BuoyancyForce(0, 0, 0);
	float inmersed = 0;

	if (h - h0 > height * 0.5) {
		inmersed = 0;
	}
	else if (h0 - h > height * 0.5) {
		inmersed = 1;
	}
	else {
		inmersed = (h0 - h) / height + 0.5;
	}
	BuoyancyForce.y = lDensity * volume * inmersed * gravity;

	particle->addForce(BuoyancyForce);
}
