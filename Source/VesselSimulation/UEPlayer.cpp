#include "VesselSimulation.h"
#include "UEPlayer.h"
#include <algorithm>
#include "VesselSimLib/IShip.h"

UEPlayer::UEPlayer() {
}


UEPlayer::~UEPlayer() {
}

void UEPlayer::control(vsl::IShip* _ship, float dt) {
	// Control rudder
	if (rudder_input_dir != 0) 
		_ship->setRudderAngle(std::max(std::min(_ship->getRequestedRudderAngle() + rudder_input_dir * 100.0f * dt, _ship->getMaxRudderAngle()), -_ship->getMaxRudderAngle()));

	// Control engine
	if (engine_input_dir != 0) 
		_ship->setEngineOrder(_ship->getEngineOrder() + engine_input_dir);
}

bool UEPlayer::isFollowingWaypoints() {
	return false;
}