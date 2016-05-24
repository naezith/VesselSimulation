#include "VesselSimulation.h"
#include "VesselSimLib/AIPlayer.h"
#include "VesselSimLib/IShip.h"
#include "VesselSimLib/Utility.h"
#include <algorithm>

vsl::AIPlayer::AIPlayer() {
	init();
}

void vsl::AIPlayer::init() {

}

void vsl::AIPlayer::control(vsl::IShip* _ship, float dt) {
	auto& wp_list = _ship->getWaypoints();
	if (wp_list.empty()) return;


	vsl::Vector target_pos = wp_list.at(0);
	vsl::Vector pos_to_target = target_pos - vsl::Vector(_ship->getPosition().x, _ship->getPosition().y, 0);

	// Rudder angle
	float target_ang = pos_to_target.toAngle();
	float angle_difference = vsl::Math::angleDifference(_ship->getRotation().z, target_ang);

	_ship->setRudderAngle(angle_difference);

	// Thrust power
	float target_distance = pos_to_target.magnitude();
	float ai_target_thrust_power = std::min(target_distance / 1000.0f, 1.0f) * _ship->getMaxThrustPower();
	if (_ship->getCurrentThrustPower() < ai_target_thrust_power) _ship->setEngineOrder(_ship->getEngineOrder() + 1);
	else if (_ship->getCurrentThrustPower() > ai_target_thrust_power) _ship->setEngineOrder(_ship->getEngineOrder() - 1);
}