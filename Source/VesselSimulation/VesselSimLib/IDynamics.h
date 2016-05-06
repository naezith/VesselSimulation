#pragma once

#include "VesselSimLib/IShip.h"
#include "VesselSimLib/DynamicData.h"

class VESSELSIMULATION_API IDynamics {
public:
	IDynamics() = default;
	~IDynamics() = default;
	virtual void update(DynamicData& _dyn, float _dt) = 0;
};