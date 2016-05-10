#include "VesselSimulation.h"
#include "VesselSimLib/Utility.h"

vsl::Vector vsl::Math::rotate(const vsl::Vector& loc, const vsl::Vector& eul) {
	vsl::Vector global;

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

int vsl::Math::sign(float a) {
	return (a > 0) ? 1 : ((a < 0) ? -1 : 0);
}

vsl::Vector::Vector() : x(0), y(0), z(0) { }

vsl::Vector::Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

const vsl::Vector vsl::Vector::Zero() { return vsl::Vector(0, 0, 0); }

vsl::Vector operator -(const vsl::Vector& right) {
	return vsl::Vector(-right.x, -right.y, -right.z);
}

vsl::Vector::Vector(const vsl::Vector& vec) :
	x(vec.x),
	y(vec.y),
	z(vec.z) { }

vsl::Vector& operator +=(vsl::Vector& left, const vsl::Vector& right) {
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;

	return left;
}

vsl::Vector& operator -=(vsl::Vector& left, const vsl::Vector& right) {
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;

	return left;
}

vsl::Vector operator +(const vsl::Vector& left, const vsl::Vector& right) {
	return vsl::Vector(left.x + right.x, left.y + right.y, left.z + right.z);
}

vsl::Vector operator -(const vsl::Vector& left, const vsl::Vector& right) {
	return vsl::Vector(left.x - right.x, left.y - right.y, left.z - right.z);
}

vsl::Vector operator *(const vsl::Vector& left, float right) {
	return vsl::Vector(left.x * right, left.y * right, left.z * right);
}

vsl::Vector operator *(float left, const vsl::Vector& right) {
	return vsl::Vector(right.x * left, right.y * left, right.z * left);
}

vsl::Vector& operator *=(vsl::Vector& left, float right) {
	left.x *= right;
	left.y *= right;
	left.z *= right;

	return left;
}

vsl::Vector operator /(const vsl::Vector& left, float right) {
	return vsl::Vector(left.x / right, left.y / right, left.z / right);
}

vsl::Vector& operator /=(vsl::Vector& left, float right) {
	left.x /= right;
	left.y /= right;
	left.z /= right;

	return left;
}

bool operator ==(const vsl::Vector& left, const vsl::Vector& right) {
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

bool operator !=(const vsl::Vector& left, const vsl::Vector& right) {
	return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}