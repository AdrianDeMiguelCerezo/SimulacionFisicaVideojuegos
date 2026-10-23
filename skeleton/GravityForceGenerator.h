#pragma once
#include "ForceGenerator.h"
#include "Vector3D.h"
class GravityForceGenerator:public ForceGenerator
{
private:
	Vector3D gravity;
public:
	GravityForceGenerator(Vector3D grav):gravity(grav) {}

	void updateForce(Particle* particle, double time) override;
};

