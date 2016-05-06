#include "VesselSimulation.h"
#include "Utility.h"

FVector vsl::Utils::rotate(const FVector& loc, const FVector& eul) {
	FVector global;

	float phi = eul.X*DEG2RAD;
	float theta = eul.Y*DEG2RAD;
	float psi = eul.Z*DEG2RAD;

	global.X = +loc.X * cos(psi) * cos(theta)
			 + loc.Y * (cos(psi) * sin(theta) * sin(phi) - sin(psi) * cos(phi))
			 + loc.Z * (cos(psi) * sin(theta) * cos(phi) + sin(psi) * sin(phi));

	global.Y = +loc.X * cos(theta) * sin(psi)
			 + loc.Y * (sin(phi) * sin(theta) * sin(psi) + cos(phi) * cos(psi))
			 + loc.Z * (cos(phi) * sin(theta) * sin(psi) - sin(phi) * cos(psi));

	global.Z = -loc.X * sin(theta)
			 + loc.Y * sin(phi) * cos(theta)
			 + loc.Z * cos(phi) * cos(theta);

	return global;
}

using vsl::Utils::Vector;

Vector::Vector() : x(0), y(0), z(0) { }

Vector::Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

Vector operator -(const Vector& right) {
	return Vector(-right.x, -right.y, -right.z);
}

Vector::Vector(const Vector& vector) :
	x(vector.x),
	y(vector.y),
	z(vector.z) { }

Vector& operator +=(Vector& left, const Vector& right) {
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;

	return left;
}

Vector& operator -=(Vector& left, const Vector& right) {
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;

	return left;
}

Vector operator +(const Vector& left, const Vector& right) {
	return Vector(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector operator -(const Vector& left, const Vector& right) {
	return Vector(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector operator *(const Vector& left, float right) {
	return Vector(left.x * right, left.y * right, left.z * right);
}

Vector operator *(float left, const Vector& right) {
	return Vector(right.x * left, right.y * left, right.z * left);
}

Vector& operator *=(Vector& left, float right) {
	left.x *= right;
	left.y *= right;
	left.z *= right;

	return left;
}

Vector operator /(const Vector& left, float right) {
	return Vector(left.x / right, left.y / right, left.z / right);
}

Vector& operator /=(Vector& left, float right) {
	left.x /= right;
	left.y /= right;
	left.z /= right;

	return left;
}

bool operator ==(const Vector& left, const Vector& right) {
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

bool operator !=(const Vector& left, const Vector& right) {
	return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}