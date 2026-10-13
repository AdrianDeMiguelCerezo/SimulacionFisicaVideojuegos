#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel_r,Vector3D acel,float damping,const physx::PxGeometry& geo) :pose(pos), vel_r(vel_r), acel(acel), damping(damping) {
	vel = Vector3D(vel_r.x / vel_s, vel.y / vel_s, vel.z / vel_s);
	renderItem = new RenderItem(CreateShape(geo), &pose, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	changeMass(0);
	changeGravity(0);
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrate(double t) {
	vel = vel * pow(damping, t);

	acel.y = gravity_s;

	//Euler explicito
	//pose.p = pose.p + (t * vel);
	//vel = vel + (t * acel);
	
	if (!init) {
		//Euler Semi-implicito
		vel = vel + (acel * t);
		pose.p = pose.p + (vel * t);
		previous_pose.p = pose.p;
		init = true;
	}
	else {
		//Verlet
		physx::PxTransform prev = previous_pose;
		previous_pose = pose;
		pose.p = 2 * pose.p - prev.p + (acel * t * t);
	}
	
	time += t;
	
}

void Particle::changeMass(float value) {
	mass_r += value;
	mass_s = mass_r * pow(vel_r.x / vel.x, 2);
}

void Particle::changeGravity(float value) {
	gravity_r += value;
	gravity_s = (vel.x / vel_r.x) * gravity_r;
	std::cout << gravity_s << " " << vel.y << " " << vel_r.y << std::endl;
}


bool Particle::isDead(Vector3D start_pos) {
	Vector3D pos = Vector3D(pose.p);
	if (time >= time_limit || (pos.magnitude() - start_pos.magnitude()>=max_distance)) {
		return true;
	}
	else {
		return false;
	}
}