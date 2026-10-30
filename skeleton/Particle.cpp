#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel_r,Vector3D acel,float damping,const physx::PxGeometry& geo,Vector4 mat) :start_pos(pos),pose(pos), vel_r(vel_r), acel(acel), damping(damping) {
	vel = Vector3D(vel_r.x / vel_s, vel_r.y / vel_s, vel_r.z / vel_s);
	renderItem = new RenderItem(CreateShape(geo), &pose, mat);

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

void Particle::integrate_semi(double t) {
	acel.y = gravity_s;
	//Euler Semi-implicito
	vel = vel + (acel * t);
	pose.p = pose.p + (vel * t);
	time += t;
}

void Particle::integrate_force(double t)
{
	acel = _force * mass_s;

	vel = vel + (acel * t);
	pose.p = pose.p + (vel * t);
	time += t;

	_force = Vector3(0, 0, 0);
}

void Particle::changeMass(float value) {
	mass_r += value;
	mass_s = mass_r * pow(vel_r.x / vel.x, 2);
}

void Particle::changeGravity(float value) {
	gravity_r += value;
	gravity_s = (vel.x / vel_r.x) * gravity_r;
}


bool Particle::isDead() {
	Vector3D pos = Vector3D(pose.p);
	if (time >= time_limit || (getDistanceBetween(pos) >= max_distance)) {
		return true;
	}
	else {
		return false;
	}
}

float Particle::getDistanceBetween(Vector3D curr_pos)
{
	Vector3D distance = curr_pos - start_pos;

	return distance.magnitude();
}

void Particle::addForce(Vector3D force)
{
	_force += force;
}

Vector3D Particle::getSimGrav(Vector3D grav_real)
{
	Vector3D modVel = (vel / vel_r);

	return Vector3D(modVel.x * grav_real.x, modVel.y * grav_real.y, modVel.z * grav_real.z);
}

Vector3D Particle::getPos()
{
	return Vector3D(pose.p);
}

Vector3D Particle::getVel()
{
	return vel;
}
