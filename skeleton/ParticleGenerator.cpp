#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3D pos, Vector3D vel_r_min, Vector3D vel_r_max, Vector3D ac, float damping, GENERATE_TYPE gt):
	vel_r_min(vel_r_min),vel_r_max(vel_r_max),acel(ac),damping(damping),gt(gt){ 
	range_x = (vel_r_max.x - vel_r_min.x) + 1;
	range_y = (vel_r_max.y - vel_r_min.y) + 1;
	range_z = (vel_r_max.z - vel_r_min.z) + 1;
}

ParticleGenerator::~ParticleGenerator() {
	for (Particle* p: particles) {
		delete p;
	}
}

void ParticleGenerator::integrate_gen(double t) {
	particles.push_back(new Particle(start_pos, 
		Vector3D((range_x * (rand() / (RAND_MAX + 1.0))), (range_y * (rand() / (RAND_MAX + 1.0))), (range_z * (rand() / (RAND_MAX + 1.0)))),
		acel, damping));

	auto it=particles.begin();
	for (Particle* p : particles) {
		p->integrate(t);
		if (p->isDead(start_pos)) {
			particles.erase(it);
			delete p;
		}
		++it;
	}

}

void ParticleGenerator::changeGravity(float value) {
	for (Particle* p : particles) {
		p->changeGravity(value);
	}
}

void ParticleGenerator::changeMass(float value) {
	for (Particle* p : particles) {
		p->changeMass(value);
	}
}