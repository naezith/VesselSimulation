// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "VesselSimLib/IShip.h"
#include "VesselActor.generated.h"

UCLASS()
class VESSELSIMULATION_API AVesselActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVesselActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	USpringArmComponent* CameraBoom;
	UCameraComponent* TopDownCameraComponent;

	int getId();
	void setId(int _id);

private:
	int id;
};
