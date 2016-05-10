#include "VesselSimulation.h"
#include "DynamicData.h"
#include "VesselSimLib/Utility.h"

vsl::DynamicData::DynamicData(vsl::Vector _pos, vsl::Vector _rot) {
	init(_pos, _rot);

	MAX_RUDDER_ANGLE = 35.0f;

	// Initialize engine orders
	m_engine_orders.push_back(-45);
	m_engine_orders.push_back(-35);
	m_engine_orders.push_back(-25);
	m_engine_orders.push_back(-17);
	m_engine_orders.push_back(0);
	m_engine_orders.push_back(21);
	m_engine_orders.push_back(37);
	m_engine_orders.push_back(75);
	m_engine_orders.push_back(100);

	// Find the 0's index, which is "stop"
	int idx = 0;
	while (m_engine_orders[idx] != 0) ++idx;
	idx_of_stop = idx;
}

void vsl::DynamicData::init(vsl::Vector _pos, vsl::Vector _rot) {
	m_pos = _pos;
	m_rot = _rot;
	m_ang_accel = m_ang_vel = m_accel = m_vel = m_global_vel = vsl::Vector(0, 0, 0);
}