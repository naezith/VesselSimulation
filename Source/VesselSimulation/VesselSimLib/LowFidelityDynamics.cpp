#include "VesselSimulation.h"
#include "VesselSimLib/LowFidelityDynamics.h"
#include "VesselSimLib/Utility.h"
#include <algorithm>

void vsl::LowFidelityDynamics::step(vsl::DynamicData& _dyn, float _dt) {
	_dyn.rudderAngle.step(_dt);
	_dyn.thrustPower.step(_dt);

	vsl::Vector& ang_accel = _dyn.m_ang_accel;
	vsl::Vector& rot = _dyn.m_rot;
	vsl::Vector& accel = _dyn.m_accel;
	vsl::Vector& vel = _dyn.m_vel;
	vsl::Vector& ang_vel = _dyn.m_ang_vel;
	vsl::Vector& pos = _dyn.m_pos;
	vsl::Vector& global_vel = _dyn.m_global_vel;

// ANGULAR
	// Angular Acceleration
	ang_accel.x = -ang_vel.z * vel.x * 0.0001f // Yaw affects roll
				- vsl::Math::sign(rot.x)* rot.x * rot.x * 0.2f; // Ship wants it's roll to be 0, drag
	ang_accel.y = +vel.x * 0.00025f // Surge affects pitch, lifts the front
				- vsl::Math::sign(rot.y)* rot.y * rot.y * 1.0f; // Ship wants it's pitch to be 0, drag
	ang_accel.z = +_dyn.rudderAngle.get() * vel.x * 0.000025f
				- vsl::Math::sign(ang_vel.z) * ang_vel.z * ang_vel.z * 0.2f;


	// Drag
	//ang_accel += -0.01f * ang_vel / _dt; // Drag

	ang_vel += ang_accel * _dt;
	rot += ang_vel * _dt;

// Vector
	// Vector Acceleration
	accel.x = 50000.0f*_dyn.thrustPower.get() // Engine causes surge
			- 0;//vsl::Math::sign(vel.x) * vel.x * vel.x * 0.0001f;
	accel.y = -ang_vel.z*20.0f // Rudder causes drift
			- ang_vel.x*20.0f // Roll causes drift
			- vsl::Math::sign(vel.y) * vel.y * vel.y * 1.0f;
	accel.z = 0;

	vel += accel * _dt;

	// Environmental forces
	float gravity = 980.0f;
	global_vel.z -= gravity * _dt; // Gravity

	global_vel.z += 1.5f * gravity * std::min(std::max((2000.0f - pos.z), 0.0f) / 25.0f, 1.0f) * _dt; // Upthrust by water

	// Convert local velocity to global velocity and add the environmental velocity
	pos += (vsl::Math::rotate(vel, rot) + global_vel) * _dt;
}