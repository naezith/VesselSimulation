#include "VesselSimulation.h"
#include "Utility.h"

using vsl::Utils::Vector;

Vector vsl::Utils::rotate(const Vector& loc, const Vector& eul) {
	Vector global;

	float phi = eul.x*DEG2RAD;
	float theta = eul.y*DEG2RAD;
	float psi = eul.z*DEG2RAD;

	global.x = +loc.x * cos(psi) * cos(theta)
			 + loc.y * (cos(psi) * sin(theta) * sin(phi) - sin(psi) * cos(phi))
			 + loc.z * (cos(psi) * sin(theta) * cos(phi) + sin(psi) * sin(phi));

	global.y = +loc.x * cos(theta) * sin(psi)
			 + loc.y * (sin(phi) * sin(theta) * sin(psi) + cos(phi) * cos(psi))
			 + loc.z * (cos(phi) * sin(theta) * sin(psi) - sin(phi) * cos(psi));

	global.z = -loc.x * sin(theta)
			 + loc.y * sin(phi) * cos(theta)
			 + loc.z * cos(phi) * cos(theta);

	return global;
}

int vsl::Utils::sign(float a) {
	return (a > 0) ? 1 : ((a < 0) ? -1 : 0);
}

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