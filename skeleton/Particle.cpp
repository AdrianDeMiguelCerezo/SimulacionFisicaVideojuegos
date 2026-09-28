#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel,Vector3 acel,float damping) :pose(pos), vel(vel),acel(acel),damping(damping) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2.0f)), &pose, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrate(double t) {
	vel = vel * pow(damping, t);
	vel = vel + (t * acel);
	pose.p = pose.p + (t * vel);
}