#pragma once
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
class Particle
{
private:
	Vector3 vel;
	Vector3 acel;
	float damping;
	physx::PxTransform previous_pose=physx::PxTransform(0,0,0);
	physx::PxTransform pose;
	RenderItem* renderItem;

public:
	Particle(Vector3 pos, Vector3 vel,Vector3 acel,float damping);
	~Particle();

	void integrate(double t);
};

