// Fill out your copyright notice in the Description page of Project Settings.

#include "VesselSimulation.h"
#include "Vessel.h"
#include "VesselSimLib/Ship.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

// Sets default values
AVessel::AVessel() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->AttachTo(RootComponent);
}

AVessel::~AVessel() {
	if (m_ship != nullptr) delete m_ship;
}

// Called when the game starts or when spawned
void AVessel::BeginPlay() {
	Super::BeginPlay();
	
	if(m_ship == nullptr){
		m_ship = new vsl::Ship();

		FRotator rot = GetActorRotation();
		FVector loc = GetActorLocation();
		m_ship->init(vsl::Utils::Vector(loc.X, loc.Y, loc.Z), vsl::Utils::Vector(rot.Roll, rot.Pitch, rot.Yaw));
	}
}

// Called every frame
void AVessel::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	// Send inputs
	m_ship->setRudderDirection(rudder_input_dir);

	if (engine_input != 0) {
		if (engine_input == 1) m_ship->incrementEngineOrder();
		else if (engine_input == -1) m_ship->decrementEngineOrder();
		engine_input = 0;
	}

	// Update
	m_ship->update(DeltaTime);

	// Get position
	vsl::Utils::Vector pos = m_ship->getPosition();
	SetActorLocation(FVector(pos.x, pos.y, pos.z));

	// Get rotation
	vsl::Utils::Vector euler_rot = m_ship->getRotation();
	SetActorRotation(FRotator(euler_rot.y, euler_rot.z, euler_rot.x));
}

// Called to bind functionality to input
void AVessel::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("IncrementEngineStep", IE_Pressed, this, &AVessel::EngineUp);
	InputComponent->BindAction("DecrementEngineStep", IE_Pressed, this, &AVessel::EngineDown);

	InputComponent->BindAction("RudderInputRight", IE_Pressed, this, &AVessel::RudderInputRight);
	InputComponent->BindAction("RudderInputRight", IE_Released, this, &AVessel::RudderInputCancelRight);
	InputComponent->BindAction("RudderInputLeft", IE_Pressed, this, &AVessel::RudderInputLeft);
	InputComponent->BindAction("RudderInputLeft", IE_Released, this, &AVessel::RudderInputCancelLeft);
}

void AVessel::RudderInputLeft() { rudder_input_dir = -1; }
void AVessel::RudderInputCancelLeft() { if (rudder_input_dir == -1) rudder_input_dir = 0; }
void AVessel::RudderInputRight() { rudder_input_dir = 1; }
void AVessel::RudderInputCancelRight() { if (rudder_input_dir == 1) rudder_input_dir = 0; }
void AVessel::EngineUp() { engine_input = 1; }
void AVessel::EngineDown() { engine_input = -1; }