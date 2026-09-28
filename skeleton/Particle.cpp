#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel,Vector3 acel) :pose(pos), vel(vel),acel(acel) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2.0f)), &pose, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrate(double t) {
	vel.x = vel.x + (t * acel.x);
	pose.p.x = pose.p.x + (t * vel.x);
}