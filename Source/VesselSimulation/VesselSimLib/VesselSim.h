#pragma once

#include <unordered_map>
#include "VesselSimLib/VesselManager.h"

namespace vsl {
	class VESSELSIMULATION_API VesselSim : public VesselManager {
	public:
		VesselSim();

		virtual void init() override;
		virtual void update(float _dt) override;

		float getGravity();
		void setGravity(float _gravity);

	private:
		float m_gravity;
	};
}