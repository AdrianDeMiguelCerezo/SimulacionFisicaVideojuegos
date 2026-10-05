#pragma once
#include "Particle.h"
class Projectile:public Particle
{
private:
	float mass_r = 0.0f;
	float gravity_r = 9.8f;

	float mass_s = 0.0f;
	float gravity_s = 0.0f;

	Vector3 vel_s;

	Vector3 acel_aux;

public:
	Projectile(Vector3 pos, Vector3 vel,Vector3 vel_s,Vector3 ac, float damping) :Particle(pos, vel, ac, damping),vel_s(vel_s),acel_aux(ac) {
		changeMass(0);
		changeGravity(0);
	}
	virtual ~Projectile() {}

	//Le suma a la masa el valor
	void changeMass(float value);

	//Le suma a la gravedad el valor
	void changeGravity(float value);

	virtual void integrate(double t) override;
};

