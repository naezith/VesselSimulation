#ifndef DYNAMICDATA_H
#define DYNAMICDATA_H

#include "VesselSimLib/Stepper.h"
#include <Runtime/Core/Public/Math/Vector.h>

class VESSELSIMULATION_API DynamicData {
    public:
		DynamicData(){}
		DynamicData(FVector _pos, FVector _rot);
		void init(FVector _pos, FVector _rot);

		float getCurrentRudderAngle();
		float getRequestedRudderAngle();
		float getCurrentThrustPower();
		float getRequestedThrustPower();

		Stepper thrustPower;
		Stepper rudderAngle;

		FVector m_ang_accel, m_ang_vel, m_rot;
		FVector m_accel, m_vel, m_pos;
		FVector m_global_vel;
		// serialize
};


#endif // DYNAMICDATA_H
