#pragma once
#include "RenderUtils.hpp"
#include <iostream>
#include "Particle.h"
using namespace physx;
class ParticleSystem;
class Firework
{
    const float pi = 3.14159265359f;
private:
    ParticleSystem* partS;
    Vector3 vel;
    PxTransform trans;
    RenderItem* rend;
    Vector3 acel;
    Vector3 gS;
    float damping;
    float mass;
    float lifetime = 0.0f;
    bool dest = false;
public:
    Firework(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damping, Vector4 c, float radius, ParticleSystem* pS);
    ~Firework();

    void update(double t);

    void integrate(double t);

    RenderItem* getRend() const { return rend; }
    PxTransform* getPos() { return &trans; }
    bool getDest() { return dest; }
};