#include "GravityForceGenerator.h"


void GravityForceGenerator::updateForce(Particle* p, double t) {
	// Check that the particle has Finite Mass
	if (fabs(p->inverse_massS) < 1e-10)return;

	// Apply the mass scaled gravity
	p->addForce(_gravity * p->massS);
}
