// Fill out your copyright notice in the Description page of Project Settings.

#include "VesselSimulation.h"
#include "VesselSpawner.h"
#include "VesselSimLib/AIPlayer.h"

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

	// Clear all the actors and real vessels
	m_actors.clear();
	vsl_sim.clearAll();

	// First position and rotation
	FVector start_pos(0, 0, 2000);
	FRotator start_rot(0, 0, 0);

	// Spawn vessels
	UWorld* const World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		for (auto i = 0; i < 4; ++i) {
			// Request a new real vessel
			vsl::IShip* new_vessel = vsl_sim.requestNewVessel("Basic Ship");

			// If delivered,
			if(new_vessel){
				int id = new_vessel->getId();
				// Create an actor for the real vessel
				AVesselActor* new_actor = World->SpawnActor<AVesselActor>(start_pos, start_rot, SpawnParams);
				if (new_actor) {
					new_actor->setId(id); // Match real vessel and actor Id's
					m_actors[id] = new_actor; // Map the id : actor

					// Initialize the real vessel
					FRotator rot = new_actor->GetActorRotation();
					FVector loc = new_actor->GetActorLocation();
					new_vessel->init(vsl::Vector(loc.X, loc.Y, loc.Z), vsl::Vector(rot.Roll, rot.Pitch, rot.Yaw));
					
					// Set the player
					if(i < 3) new_vessel->setPlayer(&ai_player);
					else new_vessel->setPlayer(&ue_player);

					// Change position and rotation for new ships
					start_pos.Y += 10000.0f;
					start_rot.Yaw += 15.0f;
				}
			}
		}
	}
}

// Called every frame
void AVesselSpawner::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );

	// Update all real vessels
	vsl_sim.update(DeltaTime);

	// Transfer vessel data to actors
	for (auto it = m_actors.begin(); it != m_actors.end(); ++it) {
		AVesselActor* act = it->second;
		vsl::IShip* sh = vsl_sim.getVessel(act->getId());

		// Get position of the actor
		vsl::Vector pos = sh->getPosition();
		act->SetActorLocation(FVector(pos.x, pos.y, pos.z));

		// Get rotation of the actor
		vsl::Vector euler_rot = sh->getRotation();
		act->SetActorRotation(FRotator(euler_rot.y, euler_rot.z, euler_rot.x));
	}

	// Engine Input is applied to all vessels controlled by UEPlayer, clear the input.
	ue_player.engine_input_dir = 0;
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

void AVesselSpawner::RudderInputLeft() { ue_player.rudder_input_dir = -1; }
void AVesselSpawner::RudderInputCancelLeft() { if (ue_player.rudder_input_dir == -1) ue_player.rudder_input_dir = 0; }
void AVesselSpawner::RudderInputRight() { ue_player.rudder_input_dir = 1; }
void AVesselSpawner::RudderInputCancelRight() { if (ue_player.rudder_input_dir == 1) ue_player.rudder_input_dir = 0; }
void AVesselSpawner::EngineUp() { ue_player.engine_input_dir = 1; }
void AVesselSpawner::EngineDown() { ue_player.engine_input_dir = -1; }


// LOGGING A VESSEL 
/*
GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString("Rudder Angle: ") + FString::SanitizeFloat(getRequestedRudderAngle()) +
FString("  |  ") + FString::SanitizeFloat(getCurrentRudderAngle()));
GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, FString("Thrust Power: ") + FString::SanitizeFloat(getRequestedThrustPower()) +
FString("  |  ") + FString::SanitizeFloat(getCurrentThrustPower()));

GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Red, FString("Position: ") + FString::SanitizeFloat(m_pos.x) +
FString(", ") + FString::SanitizeFloat(m_pos.y) +
FString(", ") + FString::SanitizeFloat(m_pos.z));
GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Red, FString("Velocity: ") + FString::SanitizeFloat(m_vel.x) +
FString(", ") + FString::SanitizeFloat(m_vel.y) +
FString(", ") + FString::SanitizeFloat(m_vel.z));
GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::Red, FString("Acceleration: ") + FString::SanitizeFloat(m_accel.x) +
FString(", ") + FString::SanitizeFloat(m_accel.y) +
FString(", ") + FString::SanitizeFloat(m_accel.z));
GEngine->AddOnScreenDebugMessage(6, 5.f, FColor::Red, FString("Angular Acceleration: ") + FString::SanitizeFloat(m_ang_accel.x) +
FString(", ") + FString::SanitizeFloat(m_ang_accel.y) +
FString(", ") + FString::SanitizeFloat(m_ang_accel.z));
GEngine->AddOnScreenDebugMessage(7, 5.f, FColor::Red, FString("Angular Velocity: ") + FString::SanitizeFloat(m_ang_vel.x) +
FString(", ") + FString::SanitizeFloat(m_ang_vel.y) +
FString(", ") + FString::SanitizeFloat(m_ang_vel.z));*/