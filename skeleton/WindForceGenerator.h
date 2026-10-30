#pragma once
#include "ForceGenerator.h"
#include "Vector3D.h"
class WindForceGenerator :public ForceGenerator
{
private:
	float coef_R;
	//Vertices para determinar el area de efecto. Vertex 1 y 2 son para los ejes x y, y el 3 es para el eje z para hacer un area tridimensional.
	//La fuerza solo se aplica si la partícula está en ese área 

	//Vertice 1. Usado para x,y,z. Los valores altos excepto en la z que es el valor bajo.
	Vector3D vertex1;

	//Vertice 2. Solo para x e y. Los valores bajos.
	Vector3D vertex2;

	//Vertice 3. Solo para z. El valor alto.
	Vector3D vertex3;

	Vector3D wind_speed;

public:
	WindForceGenerator(Vector3D vertex1, Vector3D vertex2, Vector3D vertex3, Vector3D wind_speed, float coef_R);

	void updateForce(Particle* particle, double time) override;

	bool isInRange(float value, float high, float low);
};
