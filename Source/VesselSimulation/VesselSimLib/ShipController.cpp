#include "VesselSimulation.h"
#include "VesselSimLib/ShipController.h"
#include <algorithm>

vsl::ShipController::ShipController(DynamicData* _dyn) {
	setDynamicData(_dyn);
}

void vsl::ShipController::setDynamicData(DynamicData* _dyn) {
	m_dyn.reset(_dyn);
}


// Engine 
void vsl::ShipController::setEngineOrder(int _order) {
	m_dyn->curr_engine_order = std::min(std::max(_order, getMinEngineOrder()), getMaxEngineOrder()); // Border control
	m_dyn->thrustPower.setRequested(m_dyn->m_engine_orders[m_dyn->idx_of_stop + m_dyn->curr_engine_order]); // Turn the possibly negative index into 0..array_size
}

int vsl::ShipController::getMinEngineOrder() {
	return 0 - m_dyn->idx_of_stop; // First - Index of Zero
}

int vsl::ShipController::getMaxEngineOrder() {
	return (m_dyn->m_engine_orders.size() - 1) - m_dyn->idx_of_stop; // Last - Index of Zero
}

int vsl::ShipController::getEngineOrder() {
	return m_dyn->curr_engine_order;
}

int vsl::ShipController::getRequestedThrustPower() {
	return m_dyn->thrustPower.getRequested();
}

int vsl::ShipController::getCurrentThrustPower() {
	return m_dyn->thrustPower.get();
}

// Rudder
void vsl::ShipController::setRudderAngle(float _degrees) {
	m_dyn->rudderAngle.setRequested(std::max(std::min(_degrees, getMaxRudderAngle()), -getMaxRudderAngle()));
}

float vsl::ShipController::getRequestedRudderAngle() {
	return m_dyn->rudderAngle.getRequested();
}

float vsl::ShipController::getCurrentRudderAngle() {
	return m_dyn->rudderAngle.get();
}

float vsl::ShipController::getMaxRudderAngle() {
	return m_dyn->MAX_RUDDER_ANGLE;
}