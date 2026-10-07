#pragma once
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
class Particle
{
protected:
	Vector3D vel;
	Vector3D acel;
	float damping;
	physx::PxTransform previous_pose=physx::PxTransform(0,0,0);
	physx::PxTransform pose;
	RenderItem* renderItem;
	bool init = false;

public:
	Particle(Vector3D pos, Vector3D vel,Vector3D acel,float damping, const physx::PxGeometry& geo = physx::PxSphereGeometry(2.0f));
	~Particle();

	virtual void integrate(double t,Vector3D ac=Vector3D(0,0,0));
};

