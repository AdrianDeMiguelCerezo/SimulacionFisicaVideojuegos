#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3D pos, Vector3D vel_r_min, Vector3D vel_r_max, Vector3D ac, float damping, GENERATE_TYPE gt):
	vel_r_min(vel_r_min),vel_r_max(vel_r_max),acel(ac),damping(damping),gt(gt){ 


	gen = std::mt19937(rd());
	distr_x = std::uniform_int_distribution<>(vel_r_min.x, vel_r_max.x);
	distr_y = std::uniform_int_distribution<>(vel_r_min.y, vel_r_max.y);
	distr_z = std::uniform_int_distribution<>(vel_r_min.z, vel_r_max.z);
}

ParticleGenerator::~ParticleGenerator() {
	for (Particle* p: particles) {
		delete p;
	}
}

void ParticleGenerator::integrate_gen(double t) {
	Vector3D vec = Vector3D(distr_x(gen), distr_y(gen), distr_z(gen));
	std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;
	particles.push_back(new Particle(start_pos, 
		vec,
		acel, damping));

	for (auto it = particles.begin(); it != particles.end(); ++it) {
		Particle* p = *it;
		p->integrate_semi(t);
		if (p->isDead(start_pos)) {
			it=particles.erase(it);
			delete p;
		}
		
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