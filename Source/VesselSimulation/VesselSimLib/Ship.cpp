#include "VesselSimulation.h"
#include "Ship.h"
#include <Runtime/Core/Public/Math/UnrealMathUtility.h>
#include "VesselSimLib/LowFidelityDynamics.h"

vsl::Ship::Ship() {
	thrustPower.init(0.0f, 50.0f);
	rudderAngle.init(0.0f, 10.0f);

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

	// Find the 0's index
	int idx = 0;
	while (m_engine_orders[idx] != 0) ++idx;
	m_engine_order_idx = idx;

	setDynamics(*(new LowFidelityDynamics()) );
}

void vsl::Ship::setDynamics(IDynamics& _dynamics) {
	m_dynamics.reset(&_dynamics);
}

void vsl::Ship::init(FVector _pos, FVector _rot) {
	m_pos = _pos;
	m_rot = _rot;
	m_ang_accel = m_ang_vel = m_accel = m_vel = m_global_vel = FVector(0, 0, 0);
}

FVector vsl::Ship::getPosition() {
	return m_pos;
}

FVector vsl::Ship::getRotation() {
	return m_rot;
}
void vsl::Ship::setRudderDirection(int _dir) {
	rudder_input_dir = _dir;
}

void vsl::Ship::incrementEngineOrder() {
	if (m_engine_order_idx < m_engine_orders.size() - 1)
		thrustPower.setRequested(m_engine_orders[++m_engine_order_idx]);
}

void vsl::Ship::decrementEngineOrder() {
	if (m_engine_order_idx > 0)
		thrustPower.setRequested(m_engine_orders[--m_engine_order_idx]);
}

void vsl::Ship::update(float _dt) {
	const float MAX_RUDDER_ANGLE = 35.0f; // Standard limit
	if (rudder_input_dir != 0) {
		rudderAngle.setRequested(FMath::Max(FMath::Min(rudderAngle.getRequested() + rudder_input_dir * 20.0f * _dt, MAX_RUDDER_ANGLE), -MAX_RUDDER_ANGLE));
	}
	rudderAngle.step(_dt);
	thrustPower.step(_dt);

	m_dynamics->update(*this, _dt);


	// LOGS
	//"MyCharacter's Location is %s"
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString("Rudder Angle: ") + FString::SanitizeFloat(getRequestedRudderAngle()) +
		FString("  |  ") + FString::SanitizeFloat(getCurrentRudderAngle()));
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, FString("Thrust Power: ") + FString::SanitizeFloat(getRequestedThrustPower()) +
		FString("  |  ") + FString::SanitizeFloat(getCurrentThrustPower()));

	GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Red, FString("Position: ") + FString::SanitizeFloat(m_pos.X) +
		FString(", ") + FString::SanitizeFloat(m_pos.Y) +
		FString(", ") + FString::SanitizeFloat(m_pos.Z));
	GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Red, FString("Velocity: ") + FString::SanitizeFloat(m_vel.X) +
		FString(", ") + FString::SanitizeFloat(m_vel.Y) +
		FString(", ") + FString::SanitizeFloat(m_vel.Z));
	GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::Red, FString("Acceleration: ") + FString::SanitizeFloat(m_accel.X) +
		FString(", ") + FString::SanitizeFloat(m_accel.Y) +
		FString(", ") + FString::SanitizeFloat(m_accel.Z));
	GEngine->AddOnScreenDebugMessage(6, 5.f, FColor::Red, FString("Angular Acceleration: ") + FString::SanitizeFloat(m_ang_accel.X) +
		FString(", ") + FString::SanitizeFloat(m_ang_accel.Y) +
		FString(", ") + FString::SanitizeFloat(m_ang_accel.Z));
	GEngine->AddOnScreenDebugMessage(7, 5.f, FColor::Red, FString("Angular Velocity: ") + FString::SanitizeFloat(m_ang_vel.X) +
		FString(", ") + FString::SanitizeFloat(m_ang_vel.Y) +
		FString(", ") + FString::SanitizeFloat(m_ang_vel.Z));
}
