#pragma once

#include <vector>
#include <memory>
#include "VesselSimLib/IShip.h"
#include "VesselSimLib/IDynamics.h"
#include "VesselSimLib/IController.h"

namespace vsl {
	class VESSELSIMULATION_API Ship : public IShip, public DynamicData {
	public:
		Ship();

		void init(vsl::Vector _pos, vsl::Vector _rot) override;
		void update(float _dt) override;
		vsl::Vector getPosition() override;
		vsl::Vector getRotation() override;

		virtual void log() override;
		// DYNAMICS
		void setDynamics(IDynamics& _dynamics);

		// CONTROLLER
		void setController(IController& _controller);

		// Engine 
		void setEngineOrder(int _order) override;
		int getEngineOrder() override;

		int getMinEngineOrder() override;
		int getMaxEngineOrder() override;

		int getRequestedThrustPower() override;
		int getCurrentThrustPower() override;
		int getMinThrustPower() override;
		int getMaxThrustPower() override;

		// Rudder
		void setRudderAngle(float _degrees) override;
		float getRequestedRudderAngle() override;
		float getCurrentRudderAngle() override;

		float getMaxRudderAngle() override;

	private:
		std::auto_ptr<IDynamics> m_dynamics;
		std::auto_ptr<IController> m_controller;
	};
}