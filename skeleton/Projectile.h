#pragma once
#include "Particle.h"
#include <iostream>

class Projectile:public Particle
{
private:
	float mass_r = 0.0f;
	float gravity_r = 0.0f;

	float mass_s = 0.0f;
	float gravity_s = 10.0f;

	Vector3D gravVec = Vector3(0.0f, gravity_s, 0.0f);

	Vector3D vel_real;

	Vector3D acel_aux;

public:
	Projectile(Vector3D pos, Vector3D vel,Vector3D vel_real,Vector3D ac, float damping) :Particle(pos, vel, ac, damping),vel_real(vel_real),acel_aux(ac){
		changeMass(0);
		changeGravity(0);
	}

	Projectile(Vector3D pos, Vector3D vel, Vector3D vel_real, Vector3D ac, float damping, const physx::PxGeometry& geo) :Particle(pos, vel, ac, damping,geo), vel_real(vel_real),acel_aux(ac){
		changeMass(0);
		changeGravity(0);
	}
	virtual ~Projectile() {}

	//Le suma a la masa el valor
	void changeMass(float value);

	//Le suma a la gravedad el valor
	void changeGravity(float value);

	virtual void integrate(double t,Vector3D ac=Vector3D(0,0,0)) override;
};

