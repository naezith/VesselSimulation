#include "VesselSimulation.h"
#include "VesselSimLib/VesselBuilding.h"

vsl::IShip* vsl::VesselBuilding::orderVessel(std::string type) {
	IShip* new_vessel = makeVessel(type);
	return new_vessel;
}