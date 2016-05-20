#include "VesselSimulation.h"
#include "VesselSimLib/ShipBuilding.h"
#include "VesselSimLib/Ship.h"

vsl::IShip* vsl::ShipBuilding::makeVessel(std::string type) {
	vsl::IShip* new_ship = nullptr;

	if (type == "Basic Ship") {
		new_ship = new vsl::Ship();
	}

	return new_ship;
}