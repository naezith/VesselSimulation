#pragma once

#include "VesselSimLib/DynamicData.h"

namespace vsl {
	class VESSELSIMULATION_API IDynamics {
	public:
		IDynamics() = default;
		~IDynamics() = default;
		virtual void step(DynamicData& _dyn, float _dt) = 0;
	};
}