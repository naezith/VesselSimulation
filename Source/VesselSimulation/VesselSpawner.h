// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include <unordered_map>
#include "VesselSimulation/VesselActor.h"
#include "VesselSimLib/VesselSim.h"
#include "VesselSpawner.generated.h"

UCLASS()
class VESSELSIMULATION_API AVesselSpawner : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVesselSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;



	// Vessel Simulation
	std::unordered_map<int, AVesselActor*> m_actors;
	vsl::VesselSim vsl_sim;



	// Unreal Engine Input functions
	int rudder_input_dir = 0;
	int engine_input_dir = 0;

	void RudderInputLeft();
	void RudderInputCancelLeft();
	void RudderInputRight();
	void RudderInputCancelRight();

	void EngineUp();
	void EngineDown();
};
