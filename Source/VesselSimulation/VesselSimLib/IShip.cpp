#include "VesselSimulation.h"
#include "VesselSimLib/IShip.h"

int vsl::IShip::getId() {
	return id;
}

void vsl::IShip::setId(int _id) {
	id = _id;
}