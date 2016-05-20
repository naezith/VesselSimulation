#include "VesselSimulation.h"
#include "VesselSimLib/IShip.h"

int vsl::IShip::getId() {
	return id;
}

void vsl::IShip::setId(int _id) {
	id = _id;
}

void vsl::IShip::setPlayer(IPlayer* _player) {
	m_player = _player;
}

void vsl::IShip::clearWaypoints() {
	m_waypoints.clear();
}

void vsl::IShip::addWaypoint(vsl::Vector wp) {
	m_waypoints.push_back(wp);
}

void vsl::IShip::removeWaypoint(int index) {
	if (index < m_waypoints.size())
		m_waypoints.erase(m_waypoints.begin() + index);
}

const std::vector<vsl::Vector>& vsl::IShip::getWaypoints() {
	return m_waypoints;
}

