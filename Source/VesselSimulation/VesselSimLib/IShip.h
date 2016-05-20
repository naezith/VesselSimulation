#pragma once

#include "VesselSimLib/Utility.h"
#include "VesselSimLib/IController.h"
#include "VesselSimLib/IDynamics.h"

namespace vsl {
	class VESSELSIMULATION_API IShip : public vsl::IController {
	public:
		IShip() = default;
		~IShip() = default;

		virtual void init(vsl::Vector _pos, vsl::Vector _rot) = 0;
		virtual void update(float _dt) = 0;
		virtual vsl::Vector getPosition() = 0;
		virtual vsl::Vector getRotation() = 0;
		
		int getId();
		void setId(int _id);

	private:
		int id;
	};
}
