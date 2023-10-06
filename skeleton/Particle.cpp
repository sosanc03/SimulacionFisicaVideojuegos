#include "Particle.h"

Particle::Particle(PxShape* _shape, PxTransform trans_, Vector3 v, Vector3 acc, Vector3 gsim,  float damp, const Vector4& _color) {
	acel = acc;
	damping = damp;
	trans = trans_;
	rend = new RenderItem();
	rend->color = _color;
	rend->shape = _shape;
	rend->transform = &trans_;
	vel = v;
	gS = gsim;
}

Particle::~Particle() {
	DeregisterRenderItem(rend);
	delete rend;
}


void Particle::update(float t) {
	integrate(t);
	//trans.p += vel;
	render();
}

void Particle::render() {
	rend->transform = &trans;
}

void Particle::integrate(float t)
{
	// Trivial case, infinite mass --> do nothing
	//if (inverse_massS <= 0.0f) return;
	// Update position
	(&trans)->p += vel * t;
	// Update linear velocity
	vel += acel * t;
	vel += gS * t;
	// Impose drag (damping)
	vel *= powf(damping, t);
}
