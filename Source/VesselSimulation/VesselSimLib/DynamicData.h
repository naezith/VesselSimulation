#ifndef DYNAMICDATA_H
#define DYNAMICDATA_H

#include "VesselSimLib/Stepper.h"
#include "VesselSimLib/Utility.h"

namespace vsl {
	class VESSELSIMULATION_API DynamicData {
	public:
		DynamicData() {}
		DynamicData(vsl::Utils::Vector _pos, vsl::Utils::Vector _rot);
		void init(vsl::Utils::Vector _pos, vsl::Utils::Vector _rot);

		float getCurrentRudderAngle();
		float getRequestedRudderAngle();
		float getCurrentThrustPower();
		float getRequestedThrustPower();

		Stepper thrustPower;
		Stepper rudderAngle;

		vsl::Utils::Vector m_ang_accel, m_ang_vel, m_rot, m_accel, m_vel, m_pos, m_global_vel;
		// serialize
	};
}

#endif // DYNAMICDATA_H
