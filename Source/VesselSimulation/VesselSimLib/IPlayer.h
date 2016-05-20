#pragma once

namespace vsl {
	class IShip;
	class VESSELSIMULATION_API IPlayer {
	public:
		virtual void control(vsl::IShip* _ship, float dt) = 0;
	};
}