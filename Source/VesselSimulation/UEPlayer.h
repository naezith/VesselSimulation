#pragma once

#include "VesselSimLib/IPlayer.h"

namespace vsl {
	class IShip;
}

class UEPlayer : public vsl::IPlayer {
	public:
		UEPlayer();
		~UEPlayer();

		int rudder_input_dir = 0;
		int engine_input_dir = 0;

		virtual void control(vsl::IShip* _ship, float dt);
		virtual bool isFollowingWaypoints() override;
};

