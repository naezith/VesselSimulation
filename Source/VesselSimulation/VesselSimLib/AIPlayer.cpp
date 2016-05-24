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

const float range = 100000.0f;
void vsl::AIPlayer::control(vsl::IShip* _ship, float dt) {
	auto& wp_list = _ship->getWaypoints();
	if (wp_list.empty()) return; // Leave if there isn't any waypoint left

	vsl::Vector pos_to_target;
	// Check if the ship is arrived to the waypoint and if there is a valid waypoint to go
	{
		bool has_valid_target = true;
		do {
			pos_to_target = wp_list.at(0) - _ship->getPosition();
			if(pos_to_target.magnitude() < range) { // If it's too close, ship arrived
				_ship->removeWaypoint(0); // Remove the waypoint
				if (wp_list.empty()) { // There is not any waypoint left
					// Stop the engine and set the rudder to 0
					_ship->setEngineOrder(0);
					_ship->setRudderAngle(0);
					return;
				}
			}
			else has_valid_target = true; // We have a target, we can go there
		} while (!has_valid_target); 
	}
	
	// Go the the waypoint
	{
		// Set the rudder angle
		float target_ang = pos_to_target.toAngle();
		float angle_difference = vsl::Math::angleDifference(_ship->getRotation().z, target_ang);

		_ship->setRudderAngle(angle_difference);

		// Set the thrust power
		float target_distance = pos_to_target.magnitude();
		float ai_target_thrust_power = std::min(target_distance / (range*2.0f), 1.0f) * _ship->getMaxThrustPower();
		if (_ship->getCurrentThrustPower() < ai_target_thrust_power) _ship->setEngineOrder(_ship->getEngineOrder() + 1);
		else if (_ship->getCurrentThrustPower() > ai_target_thrust_power) _ship->setEngineOrder(_ship->getEngineOrder() - 1);
	}
}