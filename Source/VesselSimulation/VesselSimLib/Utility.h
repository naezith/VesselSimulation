#pragma once

#include <Runtime/Core/Public/Math/Vector.h>

namespace vsl {
	namespace Utils {
		static const float DEG2RAD = 0.01745329251;
		FVector rotate(const FVector& loc, const FVector& eul);
	}
}