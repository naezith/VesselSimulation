#pragma once

#include "VesselSimLib/IPlayer.h"

namespace vsl {
	class IShip;
	class VESSELSIMULATION_API AIPlayer : public vsl::IPlayer {
	public:
		AIPlayer();
		void init();

		virtual void control(vsl::IShip* _ship, float dt);
	};
}