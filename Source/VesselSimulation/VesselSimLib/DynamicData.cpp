#include "VesselSimulation.h"
#include "DynamicData.h"
#include "VesselSimLib/Utility.h"

using vsl::Vector;

vsl::DynamicData::DynamicData(Vector _pos, Vector _rot) {
	init(_pos, _rot);
}

void vsl::DynamicData::init(Vector _pos, Vector _rot) {
	m_pos = _pos;
	m_rot = _rot;
	m_ang_accel = m_ang_vel = m_accel = m_vel = m_global_vel = Vector(0, 0, 0);
}


float vsl::DynamicData::getCurrentThrustPower() {
	return thrustPower.get();
}

float vsl::DynamicData::getRequestedThrustPower() {
	return thrustPower.getRequested();
}

float vsl::DynamicData::getCurrentRudderAngle() {
	return rudderAngle.get();
}

float vsl::DynamicData::getRequestedRudderAngle() {
	return rudderAngle.getRequested();
}
