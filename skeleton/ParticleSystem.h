#pragma once
#include <vector>
#include "ParticleGenerator.h"
#include "ForceGenerator.h"
class ParticleSystem
{
private:
	std::vector<Particle*> particles;
	std::vector<Particle*> projectiles;
	std::vector<ParticleGenerator*> particleGenerators;
	std::vector<ForceGenerator*> forceGenerators;

	bool forces_active = true;

public:
	ParticleSystem() {}
	~ParticleSystem();

	void addParticle(Particle* p) {
		particles.push_back(p);
	}
	void addProjectile(Particle* p) {
		projectiles.push_back(p);
	}
	void addParticleGenerator(ParticleGenerator* pg) {
		particleGenerators.push_back(pg);
	}
	void addForceGenerator(ForceGenerator* fg) {
		forceGenerators.push_back(fg);
	}
	void addForcesToParticle(Particle* p);

	void changeMasses(float value);

	void integrateSystem(double t);

};

