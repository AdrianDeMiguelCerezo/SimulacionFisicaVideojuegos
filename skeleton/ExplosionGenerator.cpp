#include "ExplosionGenerator.h"
#include "Particle.h"

void ExplosionGenerator::updateForce(Particle* particle, double time) {
	if (active) {
		Vector3D pos = particle->getPos();
		float r = sqrt(pow((pos.x - center.x), 2) + pow((pos.y - center.y), 2) + pow((pos.z - center.z), 2));
		if (r < radius) {
			Vector3D force = (pos - center) * (intensity / pow(r, 2)) * (exp(-time / time_const));
			particle->addForce(force * particle->getMass());
		}
		
	}
}