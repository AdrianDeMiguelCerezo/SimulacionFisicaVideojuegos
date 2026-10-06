#pragma once
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
class Particle
{
protected:
	Vector3 vel;
	Vector3 acel;
	float damping;
	physx::PxTransform previous_pose=physx::PxTransform(0,0,0);
	physx::PxTransform pose;
	RenderItem* renderItem;
	bool init = false;

public:
	Particle(Vector3 pos, Vector3 vel,Vector3 acel,float damping, const physx::PxGeometry& geo = physx::PxSphereGeometry(2.0f));
	~Particle();

	virtual void integrate(double t);
};

