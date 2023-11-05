#include "BurstForceGenerator.h"

void BurstForceGenerator::updateForce(Particle* p, double t) {
	// Check that the particle has Finite Mass
	if (fabs(p->inverse_massS) < 1e-10)return;

	Camera* camera = GetCamera();

	Vector3 c = Vector3(camera->getTransform().p.x + 850, camera->getTransform().p.y - 850, camera->getTransform().p.z - 850);
	//Vector3 c = Vector3(0, 0, 0);
	Vector3 pos = p->getTransform()->p;
	float r = calcR(pos, c);
	if (r <= R) {
		Vector3 burstForce = (K/pow(r, 2))* Vector3((pos.x-c.x, pos.y-c.y, pos.z-c.z)) * (pow(e, -t/T));
		p->addForce(burstForce);
	}
}

float BurstForceGenerator::calcR(Vector3 c, Vector3 p) {
	return sqrtf(pow(p.x - c.x, 2) + pow(p.y - c.y, 2) + pow(p.z - c.z, 2));
}
