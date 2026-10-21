#include "ParticleGenerator.h"
#include <algorithm>

ParticleGenerator::ParticleGenerator(Vector3D pos, Vector3D other_pos, Vector3D vel_r_min, Vector3D vel_r_max, Vector3D ac, float damping, 
	int freq,PARTICLE_COLOR pc,GENERATE_TYPE gt):
	vel_r_min(vel_r_min),vel_r_max(vel_r_max),acel(ac),damping(damping),spawn_frequency(freq),gt(gt){ 

	gen = std::mt19937(rd());
	distr_x = std::uniform_int_distribution<>(vel_r_min.x, vel_r_max.x);
	distr_y = std::uniform_int_distribution<>(vel_r_min.y, vel_r_max.y);
	distr_z = std::uniform_int_distribution<>(vel_r_min.z, vel_r_max.z);

	setVariables(pos, other_pos, pc);
}

ParticleGenerator::ParticleGenerator(Vector3D pos, Vector3D other_pos, float mean, float deviation, Vector3D ac, float damping, 
	int freq,PARTICLE_COLOR pc, GENERATE_TYPE gt):
	mean(mean),deviation(deviation),acel(ac),damping(damping), spawn_frequency(freq),gt(gt){

	gen = std::mt19937(rd());
	distr_n = std::normal_distribution<float>(mean, deviation);

	setVariables(pos, other_pos, pc);
}

ParticleGenerator::~ParticleGenerator() {
	for (Particle* p: particles) {
		delete p;
	}
}

void ParticleGenerator::setVariables(Vector3D pos, Vector3D other_pos, PARTICLE_COLOR pc)
{
	distr_x_pos = std::uniform_int_distribution<>(pos.x, other_pos.x);
	distr_y_pos = std::uniform_int_distribution<>(pos.y, other_pos.y);
	distr_z_pos = std::uniform_int_distribution<>(pos.z, other_pos.z);

	switch (pc) {
	case PARTICLE_COLOR::BLACK:
		particle_mat = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case PARTICLE_COLOR::MIST_WHITE:
		particle_mat = Vector4(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PARTICLE_COLOR::WATER_BLUE:
		particle_mat = Vector4(0.02f, 0.005f, 1.0f, 1.0f);
		break;
	}

	particles = std::vector<Particle*>(POOL_SIZE, new Particle(pos, Vector3D(0, 0, 0), Vector3D(0, 0, 0), 0.8, physx::PxSphereGeometry(2.0f), particle_mat));
}

void ParticleGenerator::integrate_gen(double t) {
	for (int i = 0;i < spawn_frequency;++i) {
		Vector3D randVec;
		switch (gt) {
		case GENERATE_TYPE::UNIFORM:
			randVec = Vector3D(distr_x(gen), distr_y(gen), distr_z(gen));
			break;
		case GENERATE_TYPE::NORMAL:
			randVec = Vector3D(distr_n(gen), distr_n(gen), distr_n(gen));
			break;
		}
		Vector3D randPos = Vector3D(distr_x_pos(gen), distr_y_pos(gen), distr_z_pos(gen));

		activateParticle(randPos, randVec);
	}


	for (int i = active_index - 1;i >= 0;--i) {
		Particle* p = particles[i];
		p->integrate_semi(t);
		if (p->isDead()) {
			deactivateParticle(i);
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

void ParticleGenerator::activateParticle(Vector3D pos, Vector3D vel)
{
	if (active_index < POOL_SIZE) {
		particles[active_index]->setPosistion(pos);
		particles[active_index]->setVelocity(vel);
		particles[active_index]->resetTime();
		active_index++;
		std::cout << active_index << std::endl;
	}
}

void ParticleGenerator::deactivateParticle(int particle_index)
{
	std::swap(particles[active_index-1], particles[particle_index]);
	active_index--;
}
