// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UParticleSystem;
class UBoxComponent;

//Class that applies a force to any pawn or physic object that enters 

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:

	//Force applied to Characters that entered the LauchPad
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float ForcePawn = 1000.0f;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float ForceObject = 500000.0f;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float DirectionPitch = 45.0f;

	UPROPERTY(EditDefaultsOnly, Category = "LaunchPad")
	UParticleSystem* LaunchFx = nullptr;

	//Overlap Extract zone 
	UPROPERTY(VisibleAnywhere, Category = "LaunchPad")
	UBoxComponent* OverlapComp = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "LaunchPad")
	UStaticMeshComponent* StaticMesh = nullptr;

private:

	//handle what happen when the LaunchPad is overlapped
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
