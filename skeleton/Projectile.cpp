#include "Projectile.h"

void Projectile::changeMass(float value) {
	mass_r += value;
	mass_s = mass_r * pow(vel_real.x / vel.x, 2);
}

void Projectile::changeGravity(float value) {
	gravity_r += value;
	gravity_s= (vel.dot(vel) / vel_real.dot(vel_real)) * gravity_r;
	std::cout << gravity_s <<" "<<vel.y<<" "<<vel_real.y<< std::endl;
}

void Projectile::integrate(double t,Vector3D ac) {

	acel_aux = Vector3D(0,gravity_s,0);
	Particle::integrate(t,acel_aux);
}