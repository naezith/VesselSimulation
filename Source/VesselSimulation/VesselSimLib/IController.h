#pragma once

namespace vsl {
	const float MAX_RUDDER_ANGLE = 35.0f; // Standard limit
	class IController {
	public:
		IController() = default;
		~IController() = default;

		// Engine 
		virtual void setEngineOrder(int _order) = 0;
		virtual int getEngineOrder() = 0;

		virtual int getMinEngineOrder() = 0;
		virtual int getMaxEngineOrder() = 0;

		virtual int getRequestedThrustPower() = 0;
		virtual int getCurrentThrustPower() = 0;
		virtual int getMinThrustPower() = 0;
		virtual int getMaxThrustPower() = 0;

		// Rudder
		virtual void setRudderAngle(float _degrees) = 0;
		virtual float getRequestedRudderAngle() = 0;
		virtual float getCurrentRudderAngle() = 0;
		virtual float getMaxRudderAngle() = 0;
	};
}