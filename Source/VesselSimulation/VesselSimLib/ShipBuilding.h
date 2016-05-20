#pragma once

#include "VesselSimLib/VesselBuilding.h"

namespace vsl {
	class VESSELSIMULATION_API ShipBuilding : public vsl::VesselBuilding {
	public:
		virtual IShip* makeVessel(std::string type);
	};
}