#include "VesselSimulation.h"
#include "VesselSimLib/Ship.h"
#include "VesselSimLib/LowFidelityDynamics.h"
#include "VesselSimLib/ShipController.h"

vsl::Ship::Ship() {
	init(vsl::Vector::Zero(), vsl::Vector::Zero());

	setDynamics( *(new LowFidelityDynamics()) );
	setController( *(new ShipController(this)) );
}

void vsl::Ship::init(vsl::Vector _pos, vsl::Vector _rot) {
	DynamicData::init(_pos, _rot);
}

void vsl::Ship::setDynamics(IDynamics& _dynamics) {
	m_dynamics.reset(&_dynamics);
}

void vsl::Ship::setController(IController& _controller) {
	m_controller.reset(&_controller);
}

vsl::Vector vsl::Ship::getPosition() {
	return m_pos;
}

vsl::Vector vsl::Ship::getRotation() {
	return m_rot;
}

void vsl::Ship::update(float _dt) {
	if (m_player != nullptr) m_player->control(this, _dt);
	if (m_dynamics.get()) m_dynamics->step(*this, _dt);
}

void vsl::Ship::log() {
	GEngine->AddOnScreenDebugMessage(701, 5.f, FColor::Yellow, FString("Rudder Angle: ") + FString::SanitizeFloat(getRequestedRudderAngle()) +
		FString("  |  ") + FString::SanitizeFloat(getCurrentRudderAngle()));
	GEngine->AddOnScreenDebugMessage(702, 5.f, FColor::Yellow, FString("Thrust Power: ") + FString::SanitizeFloat(getRequestedThrustPower()) +
		FString("  |  ") + FString::SanitizeFloat(getCurrentThrustPower()));

	GEngine->AddOnScreenDebugMessage(703, 5.f, FColor::Green, FString("Position: ") + FString::SanitizeFloat(m_pos.x) +
		FString(", ") + FString::SanitizeFloat(m_pos.y) +
		FString(", ") + FString::SanitizeFloat(m_pos.z));
	GEngine->AddOnScreenDebugMessage(704, 5.f, FColor::Green, FString("Velocity: ") + FString::SanitizeFloat(m_vel.x) +
		FString(", ") + FString::SanitizeFloat(m_vel.y) +
		FString(", ") + FString::SanitizeFloat(m_vel.z));
	GEngine->AddOnScreenDebugMessage(705, 5.f, FColor::Green, FString("Acceleration: ") + FString::SanitizeFloat(m_accel.x) +
		FString(", ") + FString::SanitizeFloat(m_accel.y) +
		FString(", ") + FString::SanitizeFloat(m_accel.z));

	GEngine->AddOnScreenDebugMessage(706, 5.f, FColor::Cyan, FString("Rotation: ") + FString::SanitizeFloat(m_rot.x) +
		FString(", ") + FString::SanitizeFloat(m_rot.y) +
		FString(", ") + FString::SanitizeFloat(m_rot.z));
	GEngine->AddOnScreenDebugMessage(707, 5.f, FColor::Cyan, FString("Angular Velocity: ") + FString::SanitizeFloat(m_ang_vel.x) +
		FString(", ") + FString::SanitizeFloat(m_ang_vel.y) +
		FString(", ") + FString::SanitizeFloat(m_ang_vel.z));
	GEngine->AddOnScreenDebugMessage(708, 5.f, FColor::Cyan, FString("Angular Acceleration: ") + FString::SanitizeFloat(m_ang_accel.x) +
		FString(", ") + FString::SanitizeFloat(m_ang_accel.y) +
		FString(", ") + FString::SanitizeFloat(m_ang_accel.z));
}


// CONTROLLER LINK
// Engine 
void vsl::Ship::setEngineOrder(int _order) {
	m_controller->setEngineOrder(_order);
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

int vsl::Ship::getMaxThrustPower() {
	return m_controller->getMaxThrustPower();
}

int vsl::Ship::getMinThrustPower() {
	return m_controller->getMinThrustPower();
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