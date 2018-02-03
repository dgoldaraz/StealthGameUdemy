// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"


// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create Overlap component

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchZoneMesh"));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Set as root
	RootComponent = StaticMesh;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchZone"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	OverlapComp->SetBoxExtent(FVector(50.0f, 50.0f, 200.0f));
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::HandleOverlap);

	OverlapComp->SetupAttachment(StaticMesh);

}

void AFPSLaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

	//Check if the other actor is a pawn or is simulating physics (Boxes)

	FRotator LaunchRotation = GetActorRotation();
	LaunchRotation.Pitch += DirectionPitch;

	FVector LaunchVector = LaunchRotation.Vector();
	
	if (OtherActor)
	{
		if (AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor))
		{
			Character->LaunchCharacter(LaunchVector * ForcePawn , true, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchFx, GetActorTransform());
		}

		if (OtherComp)
		{
			if (OtherComp->IsSimulatingPhysics())
			{
				OtherComp->AddImpulseAtLocation(LaunchVector * ForceObject, OtherActor->GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchFx, GetActorTransform());
			}
		}
	}
}

