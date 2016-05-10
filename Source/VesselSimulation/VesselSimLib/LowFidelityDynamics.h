#pragma once

#include "VesselSimLib/IDynamics.h"

namespace vsl {
	class VESSELSIMULATION_API LowFidelityDynamics : public IDynamics {
	public:
		virtual void step(DynamicData& _dyn, float _dt);
	};
}