#include "VesselSimulation.h"
#include "VesselSimLib/LowFidelityDynamics.h"
#include "VesselSimLib/Utility.h"

void vsl::LowFidelityDynamics::update(DynamicData& _dyn, float _dt) {
	FVector& ang_accel = _dyn.m_ang_accel;
	FVector& rot = _dyn.m_rot;
	FVector& accel = _dyn.m_accel;
	FVector& vel = _dyn.m_vel;
	FVector& ang_vel = _dyn.m_ang_vel;
	FVector& pos = _dyn.m_pos;
	FVector& global_vel = _dyn.m_global_vel;

// ANGULAR
	// Angular Acceleration
	ang_accel.X = -ang_vel.Z * vel.X * 0.0001f // Yaw affects roll
				- FMath::Sign(rot.X)* rot.X * rot.X * 0.2f; // Ship wants it's roll to be 0, drag
	ang_accel.Y = +vel.X * 0.00025f // Surge affects pitch, lifts the front
				- FMath::Sign(rot.Y)* rot.Y * rot.Y * 1.0f; // Ship wants it's pitch to be 0, drag
	ang_accel.Z = +_dyn.getCurrentRudderAngle() * vel.X * 0.000025f
				- FMath::Sign(ang_vel.Z) * ang_vel.Z * ang_vel.Z * 0.2f;


	// Drag
	//ang_accel += -0.01f * ang_vel / _dt; // Drag

	ang_vel += ang_accel * _dt;
	rot += ang_vel * _dt;

// VECTOR
	// Vector Acceleration
	accel.X = 50.0f*_dyn.getCurrentThrustPower() // Engine causes surge
			- FMath::Sign(vel.X) * vel.X * vel.X * 0.0001f;
	accel.Y = -ang_vel.Z*20.0f // Rudder causes drift
			- ang_vel.X*20.0f // Roll causes drift
			- FMath::Sign(vel.Y) * vel.Y * vel.Y * 1.0f;
	accel.Z = 0;

	vel += accel * _dt;

	// Environmental forces
	float gravity = 980.0f;
	global_vel.Z -= gravity * _dt; // Gravity

	global_vel.Z += 1.5f * gravity * FMath::Min(FMath::Max((2000.0f - pos.Z), 0.0f) / 25.0f, 1.0f) * _dt; // Upthrust by water

	// Convert local velocity to global velocity and add the environmental velocity
	pos += (Utils::rotate(vel, rot) + global_vel) * _dt;
}