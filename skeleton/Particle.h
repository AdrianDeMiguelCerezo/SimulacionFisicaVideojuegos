#pragma once
#include <iostream>
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
private:
	Vector3D vel_r;
	float vel_s = 15.0f;
	Vector3D vel;

	float mass_r = 0.0f;
	float mass_s = 0.0f;

	float gravity_r = 0.0f;
	float gravity_s = -10.0f;

	Vector3D acel;

	float damping;

	Vector3D start_pos;

	physx::PxTransform previous_pose=physx::PxTransform(0,0,0);
	physx::PxTransform pose;
	RenderItem* renderItem;
	bool init = false;

	float time_limit = 10.0f;
	float time = 0.0f;

	float max_distance = 5000.0f;

public:
	Particle(Vector3D pos, Vector3D vel_r,Vector3D acel,float damping, const physx::PxGeometry& geo = physx::PxSphereGeometry(2.0f),Vector4 mat=Vector4(0.0f,0.0f,0.0f,1.0f));
	~Particle();

	void integrate(double t);

	void integrate_semi(double t);

	//Le suma a la masa el valor
	void changeMass(float value);

	//Le suma a la gravedad el valor
	void changeGravity(float value);

	bool isDead();

	float getDistanceBetween(Vector3D curr_pos);
};

