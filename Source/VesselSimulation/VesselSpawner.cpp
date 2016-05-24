// Fill out your copyright notice in the Description page of Project Settings.

#include "VesselSimulation.h"
#include "VesselSpawner.h"

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

	UWorld* const World = GetWorld();
	if (World) {
		// Enable cursor
		auto controller = World->GetFirstPlayerController();
		controller->bShowMouseCursor = true;
		controller->bEnableClickEvents = true;
		controller->bEnableMouseOverEvents = true;
		controller->HitResultTraceDistance = 10000000.0f;

		// Clear all the actors and real vessels
		m_actors.clear();
		vsl_sim.clearAll();

		// First position and rotation
		FVector start_pos(0, 0, WATER_HEIGHT);
		FRotator start_rot(0, 0, 0);

		// Spawn vessels
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

	// Refresh the cursor position by getting the mouse input
	{
		FHitResult cursor;
		GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_MAX, false, cursor);
		cursor_pos = vsl::Vector(cursor.Location.X, cursor.Location.Y, 0);
	}

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

	drawUI();
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

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AVesselSpawner::LeftClick);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AVesselSpawner::LeftClickRelease);
	InputComponent->BindAction("CTRL_LeftClick", IE_Pressed, this, &AVesselSpawner::CTRL_LeftClick);
	InputComponent->BindAction("CTRL_LeftClick", IE_Released, this, &AVesselSpawner::CTRL_LeftClickRelease);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &AVesselSpawner::RightClick);
	InputComponent->BindAction("CTRL_RightClick", IE_Pressed, this, &AVesselSpawner::CTRL_RightClick);
}

void AVesselSpawner::RudderInputLeft() { ue_player.rudder_input_dir = -1; }
void AVesselSpawner::RudderInputCancelLeft() { if (ue_player.rudder_input_dir == -1) ue_player.rudder_input_dir = 0; }
void AVesselSpawner::RudderInputRight() { ue_player.rudder_input_dir = 1; }
void AVesselSpawner::RudderInputCancelRight() { if (ue_player.rudder_input_dir == 1) ue_player.rudder_input_dir = 0; }
void AVesselSpawner::EngineUp() { ue_player.engine_input_dir = 1; }
void AVesselSpawner::EngineDown() { ue_player.engine_input_dir = -1; }

void AVesselSpawner::LeftClick() {
	if (!selecting_area) {
		selecting_area = true;
		rect_pos = cursor_pos;
	}

	//clickSelectVessels(false);
}

void AVesselSpawner::LeftClickRelease() {
	if (selecting_area) {
		areaSelectVessels(rect_pos, rect_size, false);
	}
}

void AVesselSpawner::CTRL_LeftClick() {
	if (!selecting_area) {
		selecting_area = true;
		rect_pos = cursor_pos;
	}
	//clickSelectVessels(true);
}

void AVesselSpawner::CTRL_LeftClickRelease() {
	if (selecting_area) {
		areaSelectVessels(rect_pos, rect_size, true);
	}
}

void AVesselSpawner::areaSelectVessels(vsl::Vector area_pos, vsl::Vector area_size, bool ctrl) {
	selecting_area = false;

	// Fix the negative rectangle size values
	if (area_size.x < 0) {
		area_pos.x += area_size.x;
		area_size.x *= -1;
	}
	if (area_size.y < 0) {
		area_pos.y += area_size.y;
		area_size.y *= -1;
	}

	// Loop vessels
	for (auto it = m_actors.begin(); it != m_actors.end(); ++it) {
		AVesselActor* act = it->second;
		vsl::IShip* sh = vsl_sim.getVessel(act->getId());
		int id = sh->getId();
		// Get position of the ship
		vsl::Vector pos = sh->getPosition();
		if (area_pos.x <= pos.x && pos.x <= area_pos.x + area_size.x &&
			area_pos.y <= pos.y && pos.y <= area_pos.y + area_size.y) { // Ship is inside the area
			if (!vsl_sim.isVesselSelected(id)) vsl_sim.selectVessel(id);
			else if(ctrl) vsl_sim.unselectVessel(id);
		}
		else { // Ship is away from the click
			if (!ctrl) vsl_sim.unselectVessel(sh->getId());
		}
	}
}

void AVesselSpawner::RightClick() {
	vsl_sim.addWaypointToSelected(cursor_pos, true);
}

void AVesselSpawner::CTRL_RightClick() {
	vsl_sim.addWaypointToSelected(cursor_pos, false);
}

void AVesselSpawner::drawUI() {
	// Log cursor
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString("Cursor: ") + FString::SanitizeFloat(cursor_pos.x) +
	//																FString(", ") + FString::SanitizeFloat(cursor_pos.y));

	// Loop vessels
	for (auto it = m_actors.begin(); it != m_actors.end(); ++it) {
		AVesselActor* act = it->second;
		vsl::IShip* sh = vsl_sim.getVessel(act->getId());
		int id = sh->getId();

		// Draw sphere if it's selected
		if(vsl_sim.isVesselSelected(id)){
			vsl::Vector pos = sh->getPosition();
			DrawDebugSphere(
				GetWorld(),
				FVector(pos.x, pos.y, WATER_HEIGHT),
				4000,
				10,
				FColor::Magenta
			);

			auto& wp_list = sh->getWaypoints();

			// Ship to First WP
			if(!wp_list.empty()){
				vsl::Vector ship_pos = sh->getPosition();
				vsl::Vector wp_pos = wp_list[0];
				DrawDebugLine(
					GetWorld(),
					FVector(ship_pos.x, ship_pos.y, WATER_HEIGHT),
					FVector(wp_pos.x, wp_pos.y, WATER_HEIGHT),
					FColor(0, 150, 0),
					false, -1, 0,
					1000
				);
			}

			// Other WPs
			for (int i = 0; i < wp_list.size(); ++i) {
				vsl::Vector pos = wp_list[i];

				// Draw WP
				DrawDebugSphere(
					GetWorld(),
					FVector(pos.x, pos.y, WATER_HEIGHT),
					4000,
					10,
					FColor::Green
				);

				// Draw line between WPs
				if(i < wp_list.size() - 1){
					vsl::Vector next_pos = wp_list[i + 1];
					DrawDebugLine(
						GetWorld(),
						FVector(pos.x, pos.y, WATER_HEIGHT),
						FVector(next_pos.x, next_pos.y, WATER_HEIGHT),
						FColor(0, 150, 0),
						false, -1, 0,
						1000
					);
				}
			}
		}
	}

	// Update the selection rectangle
	if (selecting_area) {
		rect_size = cursor_pos - rect_pos;

		// Draw the selection rectangle
		std::vector<FVector> line_points;
		line_points.push_back(FVector(rect_pos.x, rect_pos.y, WATER_HEIGHT));
		line_points.push_back(FVector(rect_pos.x + rect_size.x, rect_pos.y, WATER_HEIGHT));
		line_points.push_back(FVector(rect_pos.x + rect_size.x, rect_pos.y + rect_size.y, WATER_HEIGHT));
		line_points.push_back(FVector(rect_pos.x, rect_pos.y + rect_size.y, WATER_HEIGHT));
		line_points.push_back(line_points[0]);

		for (int i = 0; i < line_points.size() - 1; ++i) {
			DrawDebugLine(
				GetWorld(),
				line_points[i],
				line_points[i + 1],
				FColor(255, 0, 0),
				false, -1, 0,
				3000
			);
		}
	}
}