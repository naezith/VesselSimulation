#pragma once

namespace vsl {
	namespace Utils {
		// Vector
		class Vector {
			public:
				Vector();
				Vector(float _x, float _y, float _z);
				Vector(const Vector& vector);
				float x, y, z;
		};

		// Constants
		static const float DEG2RAD = 0.01745329251;

		// Functions
		int sign(float a);
		Vector rotate(const Vector& loc, const Vector& eul);
	}
}

vsl::Utils::Vector& operator +=(vsl::Utils::Vector& left, const vsl::Utils::Vector& right);
vsl::Utils::Vector& operator -=(vsl::Utils::Vector& left, const vsl::Utils::Vector& right);
vsl::Utils::Vector operator +(const vsl::Utils::Vector& left, const vsl::Utils::Vector& right);
vsl::Utils::Vector operator -(const vsl::Utils::Vector& left, const vsl::Utils::Vector& right);
vsl::Utils::Vector operator *(const vsl::Utils::Vector& left, float right);
vsl::Utils::Vector operator *(float left, const vsl::Utils::Vector& right);
vsl::Utils::Vector& operator *=(vsl::Utils::Vector& left, float right);
vsl::Utils::Vector operator /(const vsl::Utils::Vector& left, float right);
vsl::Utils::Vector& operator /=(vsl::Utils::Vector& left, float right);
bool operator ==(const vsl::Utils::Vector& left, const vsl::Utils::Vector& right);
bool operator !=(const vsl::Utils::Vector& left, const vsl::Utils::Vector& right);