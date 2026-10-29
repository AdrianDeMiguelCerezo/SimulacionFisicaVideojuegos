#include "GravityForceGenerator.h"
#include "Particle.h"

void GravityForceGenerator::updateForce(Particle* particle, double time) {
	//Vector3D grav_sim = particle->getSimGrav(gravity);
	particle->addForce(gravity * particle->getMass());
}