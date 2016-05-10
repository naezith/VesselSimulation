#include "VesselSimulation.h"
#include "Ship.h"
#include <Runtime/Core/Public/Math/UnrealMathUtility.h>
#include "VesselSimLib/LowFidelityDynamics.h"
#include "VesselSimLib/ShipController.h"
#include "VesselSimLib/IController.h"

vsl::Ship::Ship() {
	thrustPower.init(0.0f, 50.0f);
	rudderAngle.init(0.0f, 10.0f);

	setDynamics( *(new LowFidelityDynamics()) );
	setController( *(new ShipController(this)) );
}

void vsl::Ship::setDynamics(IDynamics& _dynamics) {
	m_dynamics.reset(&_dynamics);
}

void vsl::Ship::setController(IController& _controller) {
	m_controller.reset(&_controller);
}

void vsl::Ship::init(vsl::Vector _pos, vsl::Vector _rot) {
	m_pos = _pos;
	m_rot = _rot;
	m_ang_accel = m_ang_vel = m_accel = m_vel = m_global_vel = vsl::Vector(0, 0, 0);
}

vsl::Vector vsl::Ship::getPosition() {
	return m_pos;
}

vsl::Vector vsl::Ship::getRotation() {
	return m_rot;
}

void vsl::Ship::update(float _dt) {
	if (m_dynamics.get()) m_dynamics->step(*this, _dt);


	// LOGS
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString("Rudder Angle: ") + FString::SanitizeFloat(getRequestedRudderAngle()) +
		FString("  |  ") + FString::SanitizeFloat(getCurrentRudderAngle()));
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, FString("Thrust Power: ") + FString::SanitizeFloat(getRequestedThrustPower()) +
		FString("  |  ") + FString::SanitizeFloat(getCurrentThrustPower()));

	GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Red, FString("Position: ") + FString::SanitizeFloat(m_pos.x) +
		FString(", ") + FString::SanitizeFloat(m_pos.y) +
		FString(", ") + FString::SanitizeFloat(m_pos.z));
	GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Red, FString("Velocity: ") + FString::SanitizeFloat(m_vel.x) +
		FString(", ") + FString::SanitizeFloat(m_vel.y) +
		FString(", ") + FString::SanitizeFloat(m_vel.z));
	GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::Red, FString("Acceleration: ") + FString::SanitizeFloat(m_accel.x) +
		FString(", ") + FString::SanitizeFloat(m_accel.y) +
		FString(", ") + FString::SanitizeFloat(m_accel.z));
	GEngine->AddOnScreenDebugMessage(6, 5.f, FColor::Red, FString("Angular Acceleration: ") + FString::SanitizeFloat(m_ang_accel.x) +
		FString(", ") + FString::SanitizeFloat(m_ang_accel.y) +
		FString(", ") + FString::SanitizeFloat(m_ang_accel.z));
	GEngine->AddOnScreenDebugMessage(7, 5.f, FColor::Red, FString("Angular Velocity: ") + FString::SanitizeFloat(m_ang_vel.x) +
		FString(", ") + FString::SanitizeFloat(m_ang_vel.y) +
		FString(", ") + FString::SanitizeFloat(m_ang_vel.z));
}



// CONTROLLER LINK
// Engine 
void vsl::Ship::setEngineOrder(int _order) {
	m_controller->setRudderAngle(_order);
}

int vsl::Ship::getEngineOrder() {
	return m_controller->getEngineOrder();
}

int vsl::Ship::getMinEngineOrder() {
	return m_controller->getMinEngineOrder();
}

int vsl::Ship::getMaxEngineOrder() {
	return m_controller->getMaxEngineOrder();
}


int vsl::Ship::getRequestedThrustPower() {
	return m_controller->getRequestedThrustPower();
}

int vsl::Ship::getCurrentThrustPower() {
	return m_controller->getCurrentThrustPower();
}


// Rudder
void vsl::Ship::setRudderAngle(float _degrees) {
	m_controller->setRudderAngle(_degrees);
}

float vsl::Ship::getRequestedRudderAngle() {
	return m_controller->getRequestedRudderAngle();
}

float vsl::Ship::getCurrentRudderAngle() {
	return m_controller->getCurrentRudderAngle();
}

float vsl::Ship::getMaxRudderAngle() {
	return m_controller->getMaxRudderAngle();
}