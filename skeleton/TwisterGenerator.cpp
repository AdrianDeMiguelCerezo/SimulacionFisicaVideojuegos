#include "TwisterGenerator.h"
#include "Particle.h"

TwisterGenerator::TwisterGenerator(Vector3D eye, float K,float co_r) :eye(eye), K(K),
WindForceGenerator(Vector3(eye.x+K,eye.y+K,eye.z-K),Vector3D(eye.x-K,eye.y-K,0),Vector3D(0,0,eye.z+K),Vector3D(0,0,0),co_r) { 
	always_in_range = true;
}

void TwisterGenerator::updateForce(Particle* particle, double time) {
	Vector3D pos = particle->getPos();
	wind_speed = Vector3D(-(pos.z - eye.z), 50 - (pos.y - eye.y), pos.x - eye.x);
	WindForceGenerator::updateForce(particle, time);
}
