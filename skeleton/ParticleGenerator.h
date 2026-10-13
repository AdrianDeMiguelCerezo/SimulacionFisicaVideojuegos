#pragma once
#include <vector>
#include <random>
#include "Vector3D.h"
#include "Particle.h"
class ParticleGenerator
{
public:
	enum GENERATE_TYPE { UNIFORM, NORMAL };
private:
	std::vector<Particle*> particles;
	GENERATE_TYPE gt;

	Vector3D vel_r_min;
	Vector3D vel_r_max;

	Vector3D acel;
	float damping;

	Vector3D start_pos;

	int range_x;
	int range_y;
	int range_z;



public:

	ParticleGenerator(Vector3D pos, Vector3D vel_r_min, Vector3D vel_r_max, Vector3D ac, float damping, GENERATE_TYPE gt = GENERATE_TYPE::UNIFORM);

	~ParticleGenerator();

	void integrate_gen(double t);

	void changeGravity(float value);

	void changeMass(float value);



};

