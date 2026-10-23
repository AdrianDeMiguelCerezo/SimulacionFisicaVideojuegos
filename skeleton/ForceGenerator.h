#pragma once
class Particle;
class ForceGenerator
{
public:
	ForceGenerator() = default;
	virtual void updateForce(Particle* particle, double time) = 0;
};

