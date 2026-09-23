#pragma once
#include "PxPhysics.h"
class Vector3D
{
public:
	float x, y, z;

	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(physx::PxVec3 vec);

	float magnitude() const;
	Vector3D normalize() const;

	float dot(const Vector3D& v) const;
	Vector3D cross(const Vector3D& v) const;

	void operator=(Vector3D vec);
	Vector3D operator+(Vector3D vec);
	Vector3D operator-(Vector3D vec);
	void operator+=(Vector3D vec);
	Vector3D operator*(float value);
	operator physx::PxVec3() const;
};

