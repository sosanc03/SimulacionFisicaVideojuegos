#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
using namespace physx;
class Particle
{
private:
	// datos de referencia
	/*gS = gR * powf((velS / velR), 2);
	inverse_massS = (powf(velS, 2) * inverse_mass) / powf(velR, 2);*/// m1 = ((v1^2)*m2)/(v2^2) Por igualación de 
	//energías y teniendo en cuenta que es la masa inversa
	float velR = 940;// velocidad real
	float velS = 45;// en m/s (velocidad simulada)
	float inverse_mass = 250;// masa real 4 gramos
	float inverse_massS = 883.600;// masa inversa simulada (masa real simulada 1.13 gramos)
	Vector3 gR = Vector3(0, -9.8f, 0);// gravedad real
	Vector3 gS = Vector3(0, -0.02245925758, 0);// gravedad simulada


	Vector3 vel;
	Vector3 acel;
	float damping;
	RenderItem* rend;
	PxTransform trans;
	

	bool dest = false;
	float lifetime = 0.0f;
public:
	float startTime = 0;
	Particle(PxShape* _shape, PxTransform trans_, Vector3 v, Vector3 acc, Vector3 gsim, float damp, const Vector4& _color);
	Particle(PxTransform pos, Vector3 dir);
	~Particle();
	void update(float t = 0.5);
	void render();
	void integrate(float t);
	void bullet(Vector3 dir);
	void fireball(Vector3 dir);
	void laser(Vector3 dir);

	PxTransform* getTransform() { return &trans; };
	RenderItem* getRenderItem() { return rend; };
	bool getDest() { return dest; };
};

