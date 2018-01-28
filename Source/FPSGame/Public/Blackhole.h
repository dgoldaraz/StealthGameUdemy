// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blackhole.generated.h"


class USphereComponent;

UCLASS()
class FPSGAME_API ABlackhole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackhole();

protected:

	//Visible Mesh
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp = nullptr;

	//Collision Component
	// This sphere will destroy all the objects contained inside
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* InnerSphere = nullptr;

	//This sphere will attract all the objetc contained inside
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* OuterSphere = nullptr;

	//Force of the BlackHole
	UPROPERTY(EditAnywhere, Category = "Blackhole")
	float ForceApplied = 1000.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Destruct all the objects inside a Sphere
	void Destruction(USphereComponent* Sphere);

	//Attrack all the objecst inside of the sphere to the actor position
	void Attract(USphereComponent* Sphere);
};
