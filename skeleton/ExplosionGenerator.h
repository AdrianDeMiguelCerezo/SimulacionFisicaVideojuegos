#pragma once
#include "ForceGenerator.h"
#include "Vector3D.h"
class ExplosionGenerator:public ForceGenerator
{
private:
	float radius;
	Vector3D center;
	float intensity;
	double time_const;

	double curr_time = 0;

	bool active = false;
public:
	ExplosionGenerator(float radius, Vector3D center, float intensity, double time_const) :radius(radius), center(center), intensity(intensity), time_const(time_const) {}

	void updateForce(Particle* particle, double time) override;

	void addTime(double t) {
		curr_time += t;
		if (curr_time >= 4 * time_const) {
			active = false;
		}
	}

	void explode() {
		if (!active) {
			active = true;
			curr_time = 0;
		}
		
	}
};

