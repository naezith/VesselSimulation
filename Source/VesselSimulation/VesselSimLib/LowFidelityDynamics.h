#ifndef LOWFIDELITYDYNAMICS_H
#define LOWFIDELITYDYNAMICS_H

#include "VesselSimLib/DynamicData.h"
#include "VesselSimLib/IDynamics.h"

namespace vsl {
	class VESSELSIMULATION_API LowFidelityDynamics : public IDynamics {
	public:
		virtual void step(DynamicData& _dyn, float _dt);
	};
}
#endif // LOWFIDELITYDYNAMICS_H
