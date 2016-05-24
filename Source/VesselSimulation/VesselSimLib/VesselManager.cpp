#include "VesselSimulation.h"
#include "VesselSimLib/VesselManager.h"
#include "VesselSimLib/ShipBuilding.h"

vsl::VesselManager::VesselManager() {
}

void vsl::VesselManager::init() {
	m_vessels.clear();
	available_id = 1;
}

void vsl::VesselManager::deleteVessel(int id) {
	delete m_vessels[id];
	m_vessels.erase(id);
}

vsl::IShip* vsl::VesselManager::getVessel(int id) {
	auto it = m_vessels.find(id);
	if (it != m_vessels.end()) return it->second;
	return nullptr;
}

vsl::IShip* vsl::VesselManager::requestNewVessel(std::string type) {
	vsl::VesselBuilding* vessel_maker = new vsl::ShipBuilding();

	vsl::IShip* new_vessel = vessel_maker->orderVessel(type);
	delete vessel_maker; 

	// Give it an ID
	int id = available_id++;
	new_vessel->setId(id);
	m_vessels[id] = new_vessel; // Add to map

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
		if(it->second != nullptr) delete it->second;
	}

	m_vessels.clear();
	available_id = 1;
}

vsl::VesselManager::~VesselManager() {
	clearAll();
}

void vsl::VesselManager::selectVessel(int id) {
	selected_vsl_ids.insert(id);
}

void vsl::VesselManager::unselectVessel(int id) {
	selected_vsl_ids.erase(id);
}

bool vsl::VesselManager::isVesselSelected(int id) {
	return selected_vsl_ids.find(id) != selected_vsl_ids.end();
}

void vsl::VesselManager::addWaypointToSelected(vsl::Vector pos, bool forced) {
	for (auto it = selected_vsl_ids.begin(); it != selected_vsl_ids.end(); ++it) {
		vsl::IShip* sh = getVessel(*it);

		if (forced) sh->clearWaypoints();
		sh->addWaypoint(pos);
	}
}