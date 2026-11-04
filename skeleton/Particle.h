#pragma once
#include <iostream>
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"

class ForceGenerator;
class ParticleSystem;

class Particle
{
private:
	Vector3D vel_r;
	float vel_s = 15.0f;
	Vector3D vel;

	float mass_r = 0.0f;
	float mass_s = 2.0f;

	float gravity_r = 0.0f;
	float gravity_s = -10.0f;

	Vector3D acel;

	float damping;

	bool is_projectile = false;

	Vector3D start_pos;

	physx::PxTransform previous_pose=physx::PxTransform(0,0,0);
	physx::PxTransform pose;
	RenderItem* renderItem;
	bool init = false;

	float time_limit = 20.0f;
	float time = 0.0f;

	float max_distance = 5000.0f;

	Vector3D _force = Vector3D(0, 0, 0);

	std::vector<ForceGenerator*> forceGenerators;

	ParticleSystem* ps = nullptr;

public:
	Particle(ParticleSystem* ps,Vector3D pos, Vector3D vel_r,float mass,float damping, bool is_proj=false,const physx::PxGeometry& geo = physx::PxSphereGeometry(2.0f),Vector4 mat=Vector4(0.0f,0.0f,0.0f,1.0f));
	~Particle();

	void integrate(double t);

	void integrate_semi(double t);

	void integrate_force(double t);

	//Le suma a la masa el valor
	void changeMass(float value);

	//Le suma a la gravedad el valor. Funcion que ya no se usa pero se mantiene por proposito de mantener
	//registro del trabajo anterior
	void changeGravity(float value);

	bool isDead();

	float getDistanceBetween(Vector3D curr_pos);

	void addForceGenerator(ForceGenerator* fg);

	void addForce(Vector3D force);

	Vector3D getSimForce();

	Vector3D getPos();

	Vector3D getVel();
};

