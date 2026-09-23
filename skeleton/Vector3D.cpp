#include "Vector3D.h"

Vector3D::Vector3D():x(0),y(0),z(0){
}

Vector3D::Vector3D(float x, float y, float z) :x(x), y(y), z(z) {}

Vector3D::Vector3D(physx::PxVec3 vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

float Vector3D::magnitude() const {
	return sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalize() const {
	const float m = magnitude();
	if (m > 0.0f) {
		return Vector3D(x / m, y / m, z / m);
	}
		
	return Vector3D(x,y,z);
}

float Vector3D::dot(const Vector3D& v) const
{
	return (x * v.x + y * v.y + z * v.z);
}

Vector3D Vector3D::cross(const Vector3D& v) const
{
	return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

void Vector3D::operator=(Vector3D vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Vector3D Vector3D::operator+(Vector3D vec)
{
	return Vector3D(x + vec.x, y + vec.y, z + vec.z);
}

Vector3D Vector3D::operator-(Vector3D vec)
{
	return Vector3D(x - vec.x, y - vec.y, z - vec.z);
}

void Vector3D::operator+=(Vector3D vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

Vector3D Vector3D::operator*(float value) {
	return Vector3D(x * value, y * value, z * value);
}

Vector3D::operator physx::PxVec3() const
{
	return physx::PxVec3(x, y, z);
}

