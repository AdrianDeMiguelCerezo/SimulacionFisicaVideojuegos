#include "Particle.h"
#include "ForceGenerator.h"
#include "ParticleSystem.h"

Particle::Particle(ParticleSystem* ps,Vector3D pos, Vector3D vel_r,float mass,float damping,bool is_proj,const physx::PxGeometry& geo,Vector4 mat) :
	ps(ps),start_pos(pos),pose(pos), vel_r(vel_r), mass_r(mass), damping(damping),is_projectile(is_proj) {
	vel = Vector3D(vel_r.x / vel_s, vel_r.y / vel_s, vel_r.z / vel_s);
	renderItem = new RenderItem(CreateShape(geo), &pose, mat);
	if (is_projectile)changeMass(0);
	else mass_s = mass_r;
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
	for (ForceGenerator* fg : forceGenerators) {
		if (fg->getActive()) {
			fg->updateForce(this, t);
		}
	}

	if (is_projectile) {
		_force = getSimForce();
	}

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

void Particle::addForceGenerator(ForceGenerator* fg) {
	forceGenerators.push_back(fg);
}

void Particle::addForce(Vector3D force)
{
	_force += force;
}

Vector3D Particle::getSimForce()
{
	Vector3D modVel = (vel / vel_r);

	return Vector3D(modVel.x * _force.x, modVel.y * _force.y, modVel.z * _force.z);
}

Vector3D Particle::getPos()
{
	return Vector3D(pose.p);
}

Vector3D Particle::getVel()
{
	return vel;
}
