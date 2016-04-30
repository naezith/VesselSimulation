#pragma once

#include <Runtime/Core/Public/Math/Vector.h>
class VESSELSIMULATION_API IShip {
public:
	IShip() = default;
	~IShip() = default;
	virtual void init(FVector _pos, FVector _rot) = 0;
	virtual void update(float _dt) = 0;
	virtual FVector getPosition() = 0;
	virtual FVector getRotation() = 0;
	virtual void incrementEngineOrder() = 0;
	virtual void decrementEngineOrder() = 0;
	virtual void setRudderDirection(int _dir) = 0;

	virtual float getCurrentRudderAngle() = 0;
	virtual float getRequestedRudderAngle() = 0;
	virtual float getCurrentThrustPower() = 0;
	virtual float getRequestedThrustPower() = 0;
};
