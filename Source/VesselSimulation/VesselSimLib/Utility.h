#pragma once

#include <Runtime/Core/Public/Math/Vector.h>

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
		Vector& operator +=(Vector& left, const Vector& right);
		Vector& operator -=(Vector& left, const Vector& right);
		Vector operator +(const Vector& left, const Vector& right);
		Vector operator -(const Vector& left, const Vector& right);
		Vector operator *(const Vector& left, float right);
		Vector operator *(float left, const Vector& right);
		Vector& operator *=(Vector& left, float right);
		Vector operator /(const Vector& left, float right);
		Vector& operator /=(Vector& left, float right);
		bool operator ==(const Vector& left, const Vector& right);
		bool operator !=(const Vector& left, const Vector& right);
		// Constants
		static const float DEG2RAD = 0.01745329251;

		// Functions
		FVector rotate(const FVector& loc, const FVector& eul);
	}
}