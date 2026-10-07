#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel,Vector3D acel,float damping,const physx::PxGeometry& geo) :pose(pos), vel(vel),acel(acel),damping(damping) {
	renderItem = new RenderItem(CreateShape(geo), &pose, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrate(double t,Vector3D ac) {
	vel = vel * pow(damping, t);

	if (ac == Vector3D(0, 0, 0)) {
		ac = acel;
	}

	//Euler explicito
	//pose.p = pose.p + (t * vel);
	//vel = vel + (t * acel);
	
	if (!init) {
		//Euler Semi-implicito
		vel = vel + (ac * t);
		pose.p = pose.p + (vel * t);
		previous_pose.p = pose.p;
		init = true;
	}
	else {
		//Verlet
		physx::PxTransform prev = previous_pose;
		previous_pose = pose;
		pose.p = 2 * pose.p - prev.p + (ac * t * t);
	}
	

	
}