#ifndef DYNAMICDATA_H
#define DYNAMICDATA_H

#include "VesselSimLib/Stepper.h"
#include "VesselSimLib/Utility.h"
#include <vector>

namespace vsl {
	class VESSELSIMULATION_API DynamicData {
	public:
		DynamicData() {}
		DynamicData(vsl::Vector _pos, vsl::Vector _rot);
		void init(vsl::Vector _pos, vsl::Vector _rot);

		// Rudder
		float MAX_RUDDER_ANGLE;
		Stepper rudderAngle;

		// Engine
		int idx_of_stop;
		int curr_engine_order;
		std::vector<float> m_engine_orders; // order name : rpm
		Stepper thrustPower;

		// Physics
		vsl::Vector m_ang_accel, m_ang_vel, m_rot, m_accel, m_vel, m_pos, m_global_vel;
	};
}

#endif // DYNAMICDATA_H
