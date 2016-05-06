#pragma once

#include <vector>
#include <memory>
#include "VesselSimLib/IShip.h"
#include "VesselSimLib/IDynamics.h"
#include "VesselSimLib/DynamicData.h"

class VESSELSIMULATION_API Ship : public IShip , public DynamicData {
public:
	Ship();

	void init(FVector _pos, FVector _rot) override;
	void update(float _dt) override;
	FVector getPosition() override;
	FVector getRotation() override;
	void setRudderDirection(int _dir) override;
	void incrementEngineOrder() override;
	void decrementEngineOrder() override;


	std::vector<float> m_engine_orders; // order name : rpm
	unsigned int m_engine_order_idx;

	void setDynamics(IDynamics& _dynamics);
	std::auto_ptr<IDynamics> m_dynamics;

	int rudder_input_dir = 0;
	FVector rotate(const FVector& loc, const FVector& eul);
};
