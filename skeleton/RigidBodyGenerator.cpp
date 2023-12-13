#include "RigidBodyGenerator.h"

default_random_engine generatorRB;

void RigidBodyGenerator::update(float t) {
	timeUntilNextGeneration -= t;
}

list<RigidBody*> RigidBodyGenerator::generateBodies() {
	list<RigidBody*> listRB;
	if (rb_ != nullptr) {
		if (active && timeUntilNextGeneration <= 0) { // Si debe generar (tiempo y activo)
			for (int i = 0; i < nGen; i++) {
				normal_distribution<float> d(median, var); // Se contruye aqui para poder cambiar los parametros

				Vector3 position = pos + Vector3(d(generatorRB), d(generatorRB), d(generatorRB));
				Vector3 velocity = vel + Vector3(d(generatorRB), d(generatorRB), d(generatorRB));

				RigidBody* rb = new RigidBody(scene, physics, position, velocity, Vector3(0, 0, 0), rb_->getMass(), rb_->getLifeTime(), rb_->getShape(), rb_->getColor());

				listRB.push_back(rb);
			}
			timeUntilNextGeneration = frecuency; // Actualiza el tiempo hasta la generación
		}
	}
	return listRB;
}
