#pragma once

#include "VesselSimLib/Utility.h"

namespace vsl {
	class VESSELSIMULATION_API IShip {
	public:
		IShip() = default;
		~IShip() = default;

		virtual void init(vsl::Utils::Vector _pos, vsl::Utils::Vector _rot) = 0;
		virtual void update(float _dt) = 0;
		virtual vsl::Utils::Vector getPosition() = 0;
		virtual vsl::Utils::Vector getRotation() = 0;

		virtual void incrementEngineOrder() = 0;
		virtual void decrementEngineOrder() = 0;
		virtual void setRudderDirection(int _dir) = 0;
	};
}
