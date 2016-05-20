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
	_ship->setEngineOrder(1);
	_ship->setRudderAngle(35);
	
	auto& wp_list = _ship->getWaypoints();
	if (wp_list.empty()) return;


	vsl::Vector target_pos = wp_list.at(0);
	vsl::Vector pos_to_target = target_pos - vsl::Vector(_ship->getPosition().x, _ship->getPosition().y, 0);

	// Rudder angle
	float target_ang = pos_to_target.toAngle();
	float angle_difference = vsl::Math::angleDifference(_ship->getRotation().z, target_ang);
	float ai_target_rudder_angle = -std::max(std::min((float)(_ship->getCurrentThrustPower() > 0.0f ? angle_difference*0.25f :
									vsl::Math::sign(angle_difference)*(180.0f - fabs(angle_difference))), // Converts 175 or -175 to 5 or -5 while going backwards
									_ship->getMaxRudderAngle()), -_ship->getMaxRudderAngle());

	_ship->setRudderAngle(ai_target_rudder_angle);

	// Thrust power
	float target_distance = pos_to_target.magnitude();
	float ai_target_thrust_power = std::min(target_distance / 1000.0f, 1.0f) * 100.0f; // _ship->getMaxThrustPower(); 
	if (_ship->getCurrentThrustPower() < ai_target_thrust_power) _ship->setEngineOrder(_ship->getEngineOrder() + 1);
	else if (_ship->getCurrentThrustPower() > ai_target_thrust_power) _ship->setEngineOrder(_ship->getEngineOrder() - 1);
}