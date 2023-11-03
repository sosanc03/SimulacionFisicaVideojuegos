#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem() {
    for (auto& i : particles) { partRgis->deleteParticleRegistry(i); delete i; }
    for (auto& j : fireworks) delete j;
    delete partRgis;
}

void ParticleSystem::update(float t) {
    auto it = particles.begin();
    while (it != particles.end()) {
        auto aux = it;
        ++aux;
        if ((*it)->getDest()) {
            partRgis->deleteParticleRegistry((*it));
            delete* it;
            particles.erase(it);
        }
        else { (*it)->update(t); }
        it = aux;
    }

    auto it2 = fireworks.begin();
    while (it2 != fireworks.end()) {
        auto aux = it2;
        ++aux;
        if ((*it2)->getDest()) {
            delete* it2;
            fireworks.erase(it2);
        }
        else (*it2)->update(t);
        it2 = aux;
    }
    partRgis->updateForces(t);
}

void ParticleSystem::addParticle(Particle* p) {
    particles.push_back(p);
    addGravity(p);
}

void ParticleSystem::addFirework(Firework* f) {
    fireworks.push_back(f);
}

void ParticleSystem::addGravity(Particle* p) {
    /*gS = gR * powf((velS / velR), 2);
   inverse_massS = (powf(velS, 2) * inverse_mass) / powf(velR, 2);*/// m1 = ((v1^2)*m2)/(v2^2) Por igualación de 
   //energías y teniendo en cuenta que es la masa inversa
    float velS = p->getVelS();// en m/s (velocidad simulada)
    float velR = p->getVelR();// en m/s (velocidad real)
    Vector3 gR = Vector3(0, -9.8f, 0);// gravedad real
    //Vector3 gS = Vector3(0, -0.02245925758, 0);// gravedad simulada
    Vector3 gS = gR * powf((velS / velR), 2);// gravedad simulada

    GravityForceGenerator* g = new GravityForceGenerator(gS);
    partRgis->addRegistry(g, p);// añadimos la fuerza a la particula
}
