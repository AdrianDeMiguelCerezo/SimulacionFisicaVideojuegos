#pragma once
#include <vector>
#include <random>
#include "Vector3D.h"
#include "Particle.h"
class ParticleGenerator
{
public:
	enum GENERATE_TYPE { UNIFORM, NORMAL };
	enum PARTICLE_COLOR { BLACK, MIST_WHITE, WATER_BLUE };
private:
	std::vector<Particle*> particles;
	GENERATE_TYPE gt;

	Vector4 particle_mat;

	Vector3D vel_r_min;
	Vector3D vel_r_max;

	Vector3D acel;
	float damping;

	int spawn_frequency;

	std::random_device rd;
	std::mt19937 gen;

	std::uniform_int_distribution<> distr_x_pos;
	std::uniform_int_distribution<> distr_y_pos;
	std::uniform_int_distribution<> distr_z_pos;

	std::uniform_int_distribution<> distr_x;
	std::uniform_int_distribution<> distr_y;
	std::uniform_int_distribution<> distr_z;

	std::normal_distribution<float> distr_n;

	float mean;
	float deviation;


	const int POOL_SIZE = 1000;
	int active_index = 0;


public:

	ParticleGenerator(Vector3D pos, Vector3D other_pos, Vector3D vel_r_min, Vector3D vel_r_max, Vector3D ac, float damping, 
		int freq=1,PARTICLE_COLOR pc=PARTICLE_COLOR::BLACK,GENERATE_TYPE gt = GENERATE_TYPE::UNIFORM);

	ParticleGenerator(Vector3D pos, Vector3D other_pos, float mean, float deviation, Vector3D ac, float damping, 
		int freq=1,PARTICLE_COLOR pc = PARTICLE_COLOR::BLACK, GENERATE_TYPE gt = GENERATE_TYPE::NORMAL);

	~ParticleGenerator();

	void setVariables(Vector3D pos, Vector3D other_pos, PARTICLE_COLOR pc);

	void integrate_gen(double t);

	void changeGravity(float value);

	void changeMass(float value);

	void activateParticle(Vector3D pos, Vector3D vel);

	void deactivateParticle(int particle_index);

};

