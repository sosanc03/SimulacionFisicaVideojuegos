#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other, bool gomaElastica)
	: _K(k), _resting_length(resting_length), _other(other), gomaEl(gomaElastica) {}

void SpringForceGenerator::updateForce(Particle* particle, double t) {
	Vector3 relative_pos_vector = _other->getTransform()->p - particle->getTransform()->p;
	if (!gomaEl || mayorIgual(relative_pos_vector, _resting_length)) {
		// Particle is the particle to apply the force
		Vector3 force;

		// normalize: Normalize the relative_pos_vector and returns its length.
		const float length = relative_pos_vector.normalize();
		const float delta_x = length - _resting_length;

		force = relative_pos_vector * delta_x * _K;

		particle->addForce(force);
	}
}