#pragma once

#include <vector>
#include <memory>
#include "VesselSimLib/IShip.h"
#include "VesselSimLib/IDynamics.h"
#include "VesselSimLib/DynamicData.h"

namespace vsl {
	class VESSELSIMULATION_API Ship : public IShip, public DynamicData {
	public:
		Ship();

		void init(vsl::Utils::Vector _pos, vsl::Utils::Vector _rot) override;
		void update(float _dt) override;
		vsl::Utils::Vector getPosition() override;
		vsl::Utils::Vector getRotation() override;

		// Dynamics
		void setDynamics(IDynamics& _dynamics);
		std::auto_ptr<IDynamics> m_dynamics;

		// Rudder
		void setRudderDirection(int _dir) override;
		int rudder_input_dir = 0;

		// Engine
		void incrementEngineOrder() override;
		void decrementEngineOrder() override;
		std::vector<float> m_engine_orders; // order name : rpm
		unsigned int m_engine_order_idx;
	};
}