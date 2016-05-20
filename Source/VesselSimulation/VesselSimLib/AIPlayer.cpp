#include "VesselSimulation.h"
#include "VesselSimLib/AIPlayer.h"
#include "VesselSimLib/IShip.h"

vsl::AIPlayer::AIPlayer() {
	init();
}

void vsl::AIPlayer::init() {

}

void vsl::AIPlayer::control(vsl::IShip* _ship, float dt) {
	_ship->setEngineOrder(1);
	_ship->setRudderAngle(35);
}