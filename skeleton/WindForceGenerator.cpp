#include "WindForceGenerator.h"
#include "Particle.h"

WindForceGenerator::WindForceGenerator(Vector3D vertex1, Vector3D vertex2, Vector3D vertex3, Vector3D wind_speed, float coef_R) :
	vertex1(vertex1), vertex2(vertex2), vertex3(vertex3), wind_speed(wind_speed), coef_R(coef_R) {

}

void WindForceGenerator::updateForce(Particle* particle, double time) {
	Vector3D pos = particle->getPos();
	if (isInRange(pos.x, vertex1.x, vertex2.x) && isInRange(pos.y, vertex1.y, vertex2.y) && isInRange(pos.z, vertex3.z, vertex1.z)) {
		particle->addForce((wind_speed - particle->getVel()) * coef_R);
	}
}

bool WindForceGenerator::isInRange(float value, float high, float low)
{
	return (low <= value && value <= high);
}
