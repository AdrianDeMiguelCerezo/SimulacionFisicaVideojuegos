#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem() {
	for (Particle* p : particles) {
		delete p;
	}
	for (Particle* p : projectiles) {
		delete p;
	}
	for (ParticleGenerator* pg : particleGenerators) {
		delete pg;
	}
}

void ParticleSystem::addForcesToParticle(Particle* p)
{
	for (ForceGenerator* fg : forceGenerators) {
		p->addForceGenerator(fg);
	}
}

void ParticleSystem::changeMasses(float value)
{
	for (Particle* p : projectiles) {
		p->changeMass(value);
	}
}

void ParticleSystem::integrateSystem(double t)
{
	for (Particle* p : particles) {
		p->integrate_force(t);
	}
	for (auto it = projectiles.begin(); it != projectiles.end(); ++it) {
		Particle* p = *it;
		p->integrate_force(t);

		if (p->isDead()) {
			it = projectiles.erase(it);
			delete p;
		}
		if (it == projectiles.end())break;

	}
	for (ParticleGenerator* pg : particleGenerators) {
		pg->integrate_gen(t);
	}
}
