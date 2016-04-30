#pragma once

#include <vector>
#include "VesselSimLib/IShip.h"
#include "VesselSimLib/Stepper.h"

class VESSELSIMULATION_API Ship : public IShip {
public:
	Ship();

	void init(FVector _pos, FVector _rot) override;
	void update(float _dt) override;
	FVector getPosition() override;
	FVector getRotation() override;
	void setRudderDirection(int _dir) override;
	void incrementEngineOrder() override;
	void decrementEngineOrder() override;

	float getCurrentRudderAngle() override;
	float getRequestedRudderAngle() override;
	float getCurrentThrustPower() override;
	float getRequestedThrustPower() override;


	std::vector<float> m_engine_orders; // order name : rpm
	unsigned int m_engine_order_idx;

	Stepper thrustPower;
	Stepper rudderAngle;

	int rudder_input_dir = 0;
	FVector m_ang_accel, m_ang_vel, m_rot;
	FVector m_accel, m_vel, m_pos;
	FVector m_global_vel;
	FVector rotate(const FVector& loc, const FVector& eul);
};
