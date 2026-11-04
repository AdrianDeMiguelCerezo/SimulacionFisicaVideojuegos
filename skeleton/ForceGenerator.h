#pragma once
class Particle;
class ForceGenerator
{
private:
	bool active = true;
public:
	ForceGenerator() = default;
	virtual void updateForce(Particle* particle, double time) = 0;

	void setActive(bool value) { active = value; }
	bool getActive() { return active; }
};

