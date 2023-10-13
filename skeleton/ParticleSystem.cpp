#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem() {
    for (auto& i : particles) delete i;
    for (auto& j : fireworks) delete j;
}

void ParticleSystem::update(float t) {
    auto it = particles.begin();
    while (it != particles.end()) {
        auto aux = it;
        ++aux;
        if ((*it)->getDest()) {
            delete* it;
            particles.erase(it);
        }
        else (*it)->update(t);
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
}

void ParticleSystem::addParticle(Particle* p) {
    particles.push_back(p);
}

void ParticleSystem::addFirework(Firework* f) {
    fireworks.push_back(f);
}
