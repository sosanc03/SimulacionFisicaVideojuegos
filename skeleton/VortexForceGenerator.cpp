#include "VortexForceGenerator.h"

void VortexForceGenerator::updateForce(Particle* p, double t) {
	// Check that the particle has Finite Mass
	if (fabs(p->inverse_massS) < 1e-10)return;

	Camera* camera = GetCamera();

	Vector3 c = Vector3(camera->getTransform().p.x - 1050, camera->getTransform().p.y -1050, camera->getTransform().p.z - 1050);
	//Vector3 c = Vector3(0, 0, 0);
	Vector3 pos = p->getTransform()->p;
	Vector3 vortexForce = K * calc(c, pos);
	p->addForce(vortexForce);
}

Vector3 VortexForceGenerator::calc(Vector3 c, Vector3 p) {
	return Vector3(-(p.x - c.x), (p.y, c.y) - 50, (p.z - c.z));
}
