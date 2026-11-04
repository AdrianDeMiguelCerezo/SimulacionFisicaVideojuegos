#include "ParticleGenerator.h"
#include "ParticleSystem.h"

ParticleGenerator::ParticleGenerator(ParticleSystem* ps,Vector3D pos, Vector3D other_pos, Vector3D vel_r_min, Vector3D vel_r_max, float damping, float mass,
	int freq,PARTICLE_COLOR pc,GENERATE_TYPE gt):
	ps(ps),vel_r_min(vel_r_min),vel_r_max(vel_r_max),damping(damping),mass(mass),spawn_frequency(freq),gt(gt){ 

	gen = std::mt19937(rd());
	distr_x = std::uniform_int_distribution<>(vel_r_min.x, vel_r_max.x);
	distr_y = std::uniform_int_distribution<>(vel_r_min.y, vel_r_max.y);
	distr_z = std::uniform_int_distribution<>(vel_r_min.z, vel_r_max.z);

	setVariables(pos, other_pos, pc);
}

ParticleGenerator::ParticleGenerator(ParticleSystem* ps,Vector3D pos, Vector3D other_pos, float mean, float deviation, float damping, float mass,
	int freq,PARTICLE_COLOR pc, GENERATE_TYPE gt):
	ps(ps),mean(mean),deviation(deviation),damping(damping),mass(mass), spawn_frequency(freq),gt(gt){

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
		Particle* p = new Particle(ps, randPos,randVec,mass, damping, false, physx::PxSphereGeometry(2.0f), particle_mat);
		particles.push_back(p);
		ps->addForcesToParticle(p);
	}


	for (auto it = particles.begin(); it != particles.end(); ++it) {
		Particle* p = *it;
		p->integrate_force(t);
		
		if (p->isDead()) {
			it=particles.erase(it);
			delete p;
		}
		
	}


}