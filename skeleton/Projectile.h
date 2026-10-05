#pragma once
#include "Particle.h"
class Projectile:public Particle
{
private:
	float mass = 0.0f;
	float gravity = -9.8f;

public:
	Projectile(Vector3 pos, Vector3 vel, float damping) :Particle(pos, vel, Vector3(0, gravity, 0), damping) {}

	void changeMass(float value);

	void changeSpeed(float value);
};

