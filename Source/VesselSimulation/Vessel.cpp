// Fill out your copyright notice in the Description page of Project Settings.

#include "VesselSimulation.h"
#include "Vessel.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

// Sets default values
AVessel::AVessel()
	: thrustPower(0.0f, 50.0f)
	, rudderAngle(0.0f, 10.0f)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->AttachTo(RootComponent);

	// Initialize engine orders
	m_engine_orders.push_back(-45);
	m_engine_orders.push_back(-35);
	m_engine_orders.push_back(-25);
	m_engine_orders.push_back(-17);
	m_engine_orders.push_back(0);
	m_engine_orders.push_back(21);
	m_engine_orders.push_back(37);
	m_engine_orders.push_back(75);
	m_engine_orders.push_back(100);

	// Find the 0's index
	int idx = 0;
	while (m_engine_orders[idx] != 0) ++idx;
	m_engine_order_idx = idx;
}

// Called when the game starts or when spawned
void AVessel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVessel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

// ANGULAR
	// Angular Acceleration
	const float MAX_RUDDER_ANGLE = 35.0f; // Standard limit
	if (rudder_input_dir != 0) {
		rudderAngle.setRequested(FMath::Max(FMath::Min(rudderAngle.getRequested() + rudder_input_dir * 20.0f * DeltaTime, MAX_RUDDER_ANGLE), -MAX_RUDDER_ANGLE));
	}
	rudderAngle.step(DeltaTime);
	thrustPower.step(DeltaTime);

// ANGULAR
	// Angular Acceleration
	m_ang_accel.X = - m_ang_vel.Z * m_vel.X * 0.001f // Yaw affects roll
					- FMath::Sign(m_rot.X)* m_rot.X * m_rot.X * 0.2f; // Ship wants it's roll to be 0, drag
	m_ang_accel.Y = + m_vel.X * 0.01f // Surge affects pitch, lifts the front
					- FMath::Sign(m_rot.Y)* m_rot.Y * m_rot.Y * 1.0f; // Ship wants it's pitch to be 0, drag
	m_ang_accel.Z = + rudderAngle.get() * m_vel.X * 0.001f
					- FMath::Sign(m_ang_vel.Z) * m_ang_vel.Z * m_ang_vel.Z * 0.2f;


	// Drag
	m_ang_accel += -0.01f * m_ang_vel / DeltaTime; // Drag

	m_ang_vel += m_ang_accel * DeltaTime;
	m_rot += m_ang_vel * DeltaTime;

	SetActorRotation(FRotator(m_rot.Y, m_rot.Z, m_rot.X));

// VECTOR
	// Vector Acceleration
	m_accel.X = 25.0f*thrustPower.get(); // Engine causes surge
	m_accel.Y = - m_ang_vel.Z // Rudder causes drift
				- m_ang_vel.X; // Roll causes drift
	m_accel.Z = 0;

	// Drag
	m_accel += - 0.01f * m_vel / DeltaTime; // Drag

	m_vel += m_accel * DeltaTime;
	m_global_vel = rotate(m_vel, m_rot); // Convert local velocity to global velocity

	FVector m_pos = GetActorLocation();
	m_global_vel.Z += (3150.0f - m_pos.Z) * 1500.0f * DeltaTime; // Upthrust by water

	SetActorLocation(m_pos + m_global_vel * DeltaTime);

// LOGS
	//"MyCharacter's Location is %s"
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString("Rudder Angle: ") + FString::SanitizeFloat(rudderAngle.getRequested()) +
		FString("  |  ") + FString::SanitizeFloat(rudderAngle.get()));
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, FString("Thrust Power: ") + FString::SanitizeFloat(thrustPower.getRequested()) +
		FString("  |  ") + FString::SanitizeFloat(thrustPower.get()));
}

// Called to bind functionality to input
void AVessel::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("IncrementEngineStep", IE_Pressed, this, &AVessel::IncrementEngineOrder);
	InputComponent->BindAction("DecrementEngineStep", IE_Pressed, this, &AVessel::DecrementEngineOrder);

	InputComponent->BindAction("RudderInputRight", IE_Pressed, this, &AVessel::RudderInputRight);
	InputComponent->BindAction("RudderInputRight", IE_Released, this, &AVessel::RudderInputCancelRight);
	InputComponent->BindAction("RudderInputLeft", IE_Pressed, this, &AVessel::RudderInputLeft);
	InputComponent->BindAction("RudderInputLeft", IE_Released, this, &AVessel::RudderInputCancelLeft);
}

void AVessel::RudderInputLeft() { rudder_input_dir = -1; }
void AVessel::RudderInputCancelLeft() { if (rudder_input_dir == -1) rudder_input_dir = 0; }
void AVessel::RudderInputRight() { rudder_input_dir = 1; }
void AVessel::RudderInputCancelRight() { if (rudder_input_dir == 1) rudder_input_dir = 0; }

void AVessel::IncrementEngineOrder() {
	if (m_engine_order_idx < m_engine_orders.size() - 1)
		thrustPower.setRequested(m_engine_orders[++m_engine_order_idx]);
}

void AVessel::DecrementEngineOrder() {
	if (m_engine_order_idx > 0)
		thrustPower.setRequested(m_engine_orders[--m_engine_order_idx]);
}


static const float DEG2RAD = 0.01745329251;
FVector AVessel::rotate(const FVector& loc, const FVector& eul) {
	FVector global;

	float phi = eul.X*DEG2RAD;
	float theta = eul.Y*DEG2RAD;
	float psi = eul.Z*DEG2RAD;

	global.X = +loc.X * cos(psi) * cos(theta)
		+ loc.Y * (cos(psi) * sin(theta) * sin(phi) - sin(psi) * cos(phi))
		+ loc.Z * (cos(psi) * sin(theta) * cos(phi) + sin(psi) * sin(phi));

	global.Y = +loc.X * cos(theta) * sin(psi)
		+ loc.Y * (sin(phi) * sin(theta) * sin(psi) + cos(phi) * cos(psi))
		+ loc.Z * (cos(phi) * sin(theta) * sin(psi) - sin(phi) * cos(psi));

	global.Z = -loc.X * sin(theta)
		+ loc.Y * sin(phi) * cos(theta)
		+ loc.Z * cos(phi) * cos(theta);

	return global;
}