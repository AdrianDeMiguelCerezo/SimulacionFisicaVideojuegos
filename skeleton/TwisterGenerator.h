#pragma once
#include "WindForceGenerator.h"
class TwisterGenerator:public WindForceGenerator
{
private:
	Vector3D eye;
	float K;
public:
	TwisterGenerator(Vector3D eye, float K, float co_r);

	void updateForce(Particle* particle, double time) override;
};

