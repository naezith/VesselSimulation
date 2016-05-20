#pragma once

namespace vsl {
	class Vector;

	namespace Math {
		// Functions
		int sign(float a);
		Vector rotate(const Vector& loc, const Vector& eul);
		float angleDifference(float a1, float a2);

		// Constants
		static const float DEG2RAD = 0.01745329251;
		static const float RAD2DEG = 57.2957795131;
	}

	// Vector
	class Vector {
	public:
		Vector();
		Vector(float _x, float _y, float _z);
		Vector(const Vector& vec);
		
		float magnitude();
		float toAngle();

		float x, y, z;
		
		static const Vector Zero();
	};
}


vsl::Vector& operator +=(vsl::Vector& left, const vsl::Vector& right);
vsl::Vector& operator -=(vsl::Vector& left, const vsl::Vector& right);
vsl::Vector operator +(const vsl::Vector& left, const vsl::Vector& right);
vsl::Vector operator -(const vsl::Vector& left, const vsl::Vector& right);
vsl::Vector operator *(const vsl::Vector& left, float right);
vsl::Vector operator *(float left, const vsl::Vector& right);
vsl::Vector& operator *=(vsl::Vector& left, float right);
vsl::Vector operator /(const vsl::Vector& left, float right);
vsl::Vector& operator /=(vsl::Vector& left, float right);
bool operator ==(const vsl::Vector& left, const vsl::Vector& right);
bool operator !=(const vsl::Vector& left, const vsl::Vector& right);