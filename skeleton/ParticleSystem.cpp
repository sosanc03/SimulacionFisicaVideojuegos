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
    //addGravity(p);
    //addWind(p);
    addVortex(p);
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

void ParticleSystem::addWind(Particle* p) {
    Vector3 wind = Vector3(-10, 0, 0);
    float k1 = 0.25 /*coeficiente de rozamiento con el aire*/, k2 = 0.1;
    WindForceGenerator* w = new WindForceGenerator(wind, k1, k2);
    partRgis->addRegistry(w, p);// añadimos la fuerza a la particula
}

void ParticleSystem::addVortex(Particle* p) {
    Vector3 wind = Vector3(-10, 0, 0);
    float k = 0.0001 /*constante de fuerza del torbellino*/;
    VortexForceGenerator* v = new VortexForceGenerator(k, wind);
    partRgis->addRegistry(v, p);// añadimos la fuerza a la particula
}