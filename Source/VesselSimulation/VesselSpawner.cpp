// Fill out your copyright notice in the Description page of Project Settings.

#include "VesselSimulation.h"
#include "VesselSpawner.h"
#include <algorithm>


// Sets default values
AVesselSpawner::AVesselSpawner() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AVesselSpawner::BeginPlay() {
	Super::BeginPlay();

	vessels.clear();

	FVector start_pos(0, 0, 2000);
	FRotator start_rot(0, 0, 0);

	// Spawn vessels
	UWorld* const World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		for (auto i = 0; i < 4; ++i) {
			AVesselActor* newVessel = World->SpawnActor<AVesselActor>(start_pos, start_rot, SpawnParams);
			if (newVessel) {
				vessels.push_back(newVessel);
				start_pos.Y += 10000.0f;
				start_rot.Yaw += 15.0f;
			}
		}
	}
}

// Called every frame
void AVesselSpawner::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );

	// Send inputs to all
	if (rudder_input_dir != 0) {
		for(auto* v : vessels)
			v->m_ship->setRudderAngle(std::max(std::min(v->m_ship->getRequestedRudderAngle() + rudder_input_dir * 100.0f * DeltaTime, v->m_ship->getMaxRudderAngle()), -v->m_ship->getMaxRudderAngle()));
	}

	if (engine_input_dir != 0) {
		for (auto* v : vessels) 
			v->m_ship->setEngineOrder(v->m_ship->getEngineOrder() + engine_input_dir);

		engine_input_dir = 0;
	}

	// Update all
	for (auto* v : vessels){
		// Update
		v->m_ship->update(DeltaTime);

		// Get position
		vsl::Vector pos = v->m_ship->getPosition();
		v->SetActorLocation(FVector(pos.x, pos.y, pos.z));

		// Get rotation
		vsl::Vector euler_rot = v->m_ship->getRotation();
		v->SetActorRotation(FRotator(euler_rot.y, euler_rot.z, euler_rot.x));
	}
}

// Called to bind functionality to input
void AVesselSpawner::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("IncrementEngineStep", IE_Pressed, this, &AVesselSpawner::EngineUp);
	InputComponent->BindAction("DecrementEngineStep", IE_Pressed, this, &AVesselSpawner::EngineDown);

	InputComponent->BindAction("RudderInputRight", IE_Pressed, this, &AVesselSpawner::RudderInputRight);
	InputComponent->BindAction("RudderInputRight", IE_Released, this, &AVesselSpawner::RudderInputCancelRight);
	InputComponent->BindAction("RudderInputLeft", IE_Pressed, this, &AVesselSpawner::RudderInputLeft);
	InputComponent->BindAction("RudderInputLeft", IE_Released, this, &AVesselSpawner::RudderInputCancelLeft);
}

void AVesselSpawner::RudderInputLeft() { rudder_input_dir = -1; }
void AVesselSpawner::RudderInputCancelLeft() { if (rudder_input_dir == -1) rudder_input_dir = 0; }
void AVesselSpawner::RudderInputRight() { rudder_input_dir = 1; }
void AVesselSpawner::RudderInputCancelRight() { if (rudder_input_dir == 1) rudder_input_dir = 0; }
void AVesselSpawner::EngineUp() { engine_input_dir = 1; }
void AVesselSpawner::EngineDown() { engine_input_dir = -1; }