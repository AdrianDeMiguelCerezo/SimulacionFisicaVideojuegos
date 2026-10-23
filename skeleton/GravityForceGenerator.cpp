#include "GravityForceGenerator.h"
#include "Particle.h"

void GravityForceGenerator::updateForce(Particle* particle, double time) {
	particle->addForce(gravity * particle->getMass());
}