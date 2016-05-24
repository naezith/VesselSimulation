#pragma once

#include "VesselSimLib/DynamicData.h"
#include "VesselSimLib/IController.h"
#include <memory>

namespace vsl {
	class VESSELSIMULATION_API ShipController : public IController {
	public:
		ShipController(DynamicData* _dyn);
		void setDynamicData(DynamicData* _dyn);

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
		std::auto_ptr<DynamicData> m_dyn;
	};
}