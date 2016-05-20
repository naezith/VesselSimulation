#include "VesselSimulation.h"
#include "VesselSimLib/VesselBuilding.h"

vsl::IShip* vsl::VesselBuilding::orderVessel(std::string type) {
	return makeVessel(type);
}