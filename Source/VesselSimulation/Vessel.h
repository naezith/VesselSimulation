// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "GameFramework/Pawn.h"
#include "Stepper.h"
#include "Vessel.generated.h"


UCLASS()
class VESSELSIMULATION_API AVessel : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVessel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	// Vessel Control
	/*
	class Stepper {
	public:
		Stepper() {}
		Stepper(float _init, float _speed) : m_current(_init), m_requested(_init), m_speed(FMath::Abs(_speed)) {}

		void step(float _dt) {
			if (m_current < m_requested) {
				m_current += m_speed*_dt;
				if (m_current > m_requested) m_current = m_requested;
			}
			else if (m_current > m_requested) {
				m_current -= m_speed*_dt;
				if (m_current < m_requested) m_current = m_requested;
			}
		}

		float get() { return m_current; }
		float setSpeed(float _speed) { m_speed = FMath::Abs(_speed); }
		float getRequested() { return m_requested; }
		void setRequested(float _requested) { m_requested = _requested; }

		void reset(float _value) { m_current = _value; }

	private:
		float m_current;
		float m_speed;
		float m_requested;
	};
	*/
	Stepper thrustPower;
	Stepper rudderAngle;


	//Input functions
	int rudder_input_dir = 0;
	void RudderInputLeft();
	void RudderInputCancelLeft();
	void RudderInputRight();
	void RudderInputCancelRight();

	std::vector<float> m_engine_orders; // order name : rpm
	unsigned int m_engine_order_idx;
	void IncrementEngineOrder();
	void DecrementEngineOrder();


	FVector m_ang_accel, m_ang_vel, m_rot;
	FVector m_accel, m_vel;
	FVector m_global_vel;
	FVector rotate(const FVector& loc, const FVector& eul);
};


