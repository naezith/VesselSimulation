#include "VesselSimulation.h"
#include "VesselSimLib/VesselManager.h"
#include "VesselSimLib/ShipBuilding.h"

vsl::VesselManager::VesselManager() {
	init();
}

void vsl::VesselManager::init() {
	m_vessels.clear();
}

void vsl::VesselManager::deleteVessel(int id) {
	delete m_vessels[id];
	m_vessels.erase(id);
}

vsl::IShip* vsl::VesselManager::getVessel(int id) {
	return m_vessels[id];
}

vsl::IShip* vsl::VesselManager::requestNewVessel(std::string type) {
	vsl::VesselBuilding* vessel_maker = new vsl::ShipBuilding();

	vsl::IShip* new_vessel = vessel_maker->orderVessel("Basic Ship");
	delete vessel_maker; 

	m_vessels[available_id++] = new_vessel; // Add to list
	return new_vessel; // Deliver the vessel
}

void vsl::VesselManager::update(float _dt) {
	// Update all vessels
	for (auto it = m_vessels.begin(); it != m_vessels.end(); ++it) {
		vsl::IShip* vsl = it->second;

		// Update
		vsl->update(_dt);
	}
}

void vsl::VesselManager::clearAll() {
	for (auto it = m_vessels.begin(); it != m_vessels.end(); ++it) {
		delete it->second;
	}

	m_vessels.clear();
	available_id = 0;
}

vsl::VesselManager::~VesselManager() {
	clearAll();
}