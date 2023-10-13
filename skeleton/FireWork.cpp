#include "Firework.h"
#include "ParticleSystem.h"

Firework::Firework(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damp, Vector4 c, float radius, ParticleSystem* pS)
    : trans(pos), vel(vel), acel(acc), gS(grav), mass(weight), damping(damp), partS(pS)
{
    rend = new RenderItem();
    rend->color = c;
    rend->shape = CreateShape(physx::PxSphereGeometry(radius));
    rend->transform = &trans;
    RegisterRenderItem(rend);
}

Firework::~Firework()
{
    Vector3 dir;
    float angle;
    for (int i = 0; i < 8; i++) {
        angle = (360 / 8) * i;
        dir = Vector3(cos(angle * pi/180), sin(angle * pi / 180), 1);
        Particle* part = new Particle(trans, dir);
        partS->addParticle(part);
    }
    DeregisterRenderItem(rend);
    delete rend;
}

void Firework::update(double t)
{
    integrate(t);
    //tiempo de vida (si es mayor que 5 segundos se borra)  
    lifetime += t;
    //comprobar si se tiene que borrar
    if (trans.p.y < 20 || lifetime >= 5) dest = true;
}


void Firework::integrate(double t)
{
    trans.p += vel * t;
    vel += (gS + acel) * t;
    vel *= pow(damping, t);
}