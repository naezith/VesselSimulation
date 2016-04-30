#include "VesselSimulation.h"
#include "Ship.h"
#include <Runtime/Core/Public/Math/UnrealMathUtility.h>

Ship::Ship()
	: thrustPower(0.0f, 50.0f)
	, rudderAngle(0.0f, 10.0f) {

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
}

void Ship::init(FVector _pos, FVector _rot) {
	m_pos = _pos;
	m_rot = _rot;
	m_ang_accel = m_ang_vel = m_accel = m_vel = m_global_vel = FVector(0, 0, 0);
}

FVector Ship::getPosition() {
	return m_pos;
}

FVector Ship::getRotation() {
	return m_rot;
}
void Ship::setRudderDirection(int _dir) {
	rudder_input_dir = _dir;
}

void Ship::incrementEngineOrder() {
	if (m_engine_order_idx < m_engine_orders.size() - 1)
		thrustPower.setRequested(m_engine_orders[++m_engine_order_idx]);
}

void Ship::decrementEngineOrder() {
	if (m_engine_order_idx > 0)
		thrustPower.setRequested(m_engine_orders[--m_engine_order_idx]);
}

float Ship::getCurrentThrustPower() {
	return thrustPower.get();
}

float Ship::getRequestedThrustPower() {
	return thrustPower.getRequested();
}

float Ship::getCurrentRudderAngle() {
	return rudderAngle.get();
}

float Ship::getRequestedRudderAngle() {
	return rudderAngle.getRequested();
}

void Ship::update(float _dt) {
	const float MAX_RUDDER_ANGLE = 35.0f; // Standard limit
	if (rudder_input_dir != 0) {
		rudderAngle.setRequested(FMath::Max(FMath::Min(rudderAngle.getRequested() + rudder_input_dir * 20.0f * _dt, MAX_RUDDER_ANGLE), -MAX_RUDDER_ANGLE));
	}
	rudderAngle.step(_dt);
	thrustPower.step(_dt);

	// ANGULAR
	// Angular Acceleration
	m_ang_accel.X = - m_ang_vel.Z * m_vel.X * 0.0001f // Yaw affects roll
					-FMath::Sign(m_rot.X)* m_rot.X * m_rot.X * 0.2f; // Ship wants it's roll to be 0, drag
	m_ang_accel.Y = + m_vel.X * 0.00025f // Surge affects pitch, lifts the front
					-FMath::Sign(m_rot.Y)* m_rot.Y * m_rot.Y * 1.0f; // Ship wants it's pitch to be 0, drag
	m_ang_accel.Z = + rudderAngle.get() * m_vel.X * 0.000025f
					- FMath::Sign(m_ang_vel.Z) * m_ang_vel.Z * m_ang_vel.Z * 0.2f;


	// Drag
	//m_ang_accel += -0.01f * m_ang_vel / _dt; // Drag

	m_ang_vel += m_ang_accel * _dt;
	m_rot += m_ang_vel * _dt;

	// VECTOR
	// Vector Acceleration
	m_accel.X = 50.0f*thrustPower.get() // Engine causes surge
				- FMath::Sign(m_vel.X) * m_vel.X * m_vel.X * 0.001f; 
	m_accel.Y = - m_ang_vel.Z*20.0f // Rudder causes drift
				- m_ang_vel.X*20.0f // Roll causes drift
				-FMath::Sign(m_vel.Y) * m_vel.Y * m_vel.Y * 1.0f;
	m_accel.Z = 0; 

	m_vel += m_accel * _dt;

	// Environmental forces
	float gravity = 980.0f;
	m_global_vel.Z -= gravity * _dt; // Gravity
	
	m_global_vel.Z += 1.5f * gravity * FMath::Min(FMath::Max((2000.0f - m_pos.Z), 0.0f) / 25.0f, 1.0f) * _dt; // Upthrust by water

	// Convert local velocity to global velocity and add the environmental velocity
	m_pos += (rotate(m_vel, m_rot) + m_global_vel) * _dt;

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

static const float DEG2RAD = 0.01745329251;
FVector Ship::rotate(const FVector& loc, const FVector& eul) {
	FVector global;

	float phi = eul.X*DEG2RAD;
	float theta = eul.Y*DEG2RAD;
	float psi = eul.Z*DEG2RAD;

	global.X = +loc.X * cos(psi) * cos(theta)
		+ loc.Y * (cos(psi) * sin(theta) * sin(phi) - sin(psi) * cos(phi))
		+ loc.Z * (cos(psi) * sin(theta) * cos(phi) + sin(psi) * sin(phi));

	global.Y = +loc.X * cos(theta) * sin(psi)
		+ loc.Y * (sin(phi) * sin(theta) * sin(psi) + cos(phi) * cos(psi))
		+ loc.Z * (cos(phi) * sin(theta) * sin(psi) - sin(phi) * cos(psi));

	global.Z = -loc.X * sin(theta)
		+ loc.Y * sin(phi) * cos(theta)
		+ loc.Z * cos(phi) * cos(theta);

	return global;
}
