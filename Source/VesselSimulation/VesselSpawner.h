// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include <unordered_map>
#include "VesselSimulation/VesselActor.h"
#include "VesselSimLib/VesselSim.h"
#include "VesselSimulation/UEPlayer.h"
#include "VesselSimLib/AIPlayer.h"
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

	void drawUI();

	// Unreal Engine Player and Input functions
	UEPlayer ue_player;
	vsl::AIPlayer ai_player;

	void RudderInputLeft();
	void RudderInputCancelLeft();
	void RudderInputRight();
	void RudderInputCancelRight();
	void EngineUp();
	void EngineDown();

	vsl::Vector cursor_pos;
	void LeftClick();
	void LeftClickRelease();
	void CTRL_LeftClick();
	void CTRL_LeftClickRelease();
	
	void areaSelectVessels(vsl::Vector area_pos, vsl::Vector area_size, bool ctrl);

	void RightClick();
	void CTRL_RightClick();

	const float WATER_HEIGHT = 2000.0f;

	// Area select
	bool selecting_area = false;
	vsl::Vector rect_pos;
	vsl::Vector rect_size;
};
