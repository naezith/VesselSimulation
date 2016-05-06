#include "VesselSimulation.h"
#include "DynamicData.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"

DynamicData::DynamicData(FVector _pos, FVector _rot) {
	init(_pos, _rot);
}

void DynamicData::init(FVector _pos, FVector _rot) {
	m_pos = _pos;
	m_rot = _rot;
	m_ang_accel = m_ang_vel = m_accel = m_vel = m_global_vel = FVector(0, 0, 0);
}


float DynamicData::getCurrentThrustPower() {
	return thrustPower.get();
}

float DynamicData::getRequestedThrustPower() {
	return thrustPower.getRequested();
}

float DynamicData::getCurrentRudderAngle() {
	return rudderAngle.get();
}

float DynamicData::getRequestedRudderAngle() {
	return rudderAngle.getRequested();
}
