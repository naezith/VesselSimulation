#pragma once

#include "VesselSimLib/IShip.h"

namespace vsl {
	class VESSELSIMULATION_API VesselBuilding {
	public:
		IShip* orderVessel(std::string type);

	protected:
		virtual IShip* makeVessel(std::string type) = 0;
	};
}