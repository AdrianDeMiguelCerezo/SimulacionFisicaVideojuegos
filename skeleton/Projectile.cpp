#include "Projectile.h"

void Projectile::changeMass(float value) {
	mass_r += value;
	mass_s = mass_r * pow(vel.x / vel_s.x, 2);
}

void Projectile::changeGravity(float value) {
	gravity_r += value;
	gravity_s= gravity_r * pow(vel_s.x / vel.x, 2);
}

void Projectile::integrate(double t) {

	acel_aux.y =gravity_s;
	acel = mass_s * acel_aux;
	Particle::integrate(t);
}