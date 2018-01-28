// Fill out your copyright notice in the Description page of Project Settings.

#include "Blackhole.h"
#include "Components/SphereComponent.h"

// Sets default values
ABlackhole::ABlackhole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	//Create Inner Sphere
	InnerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphere"));
	InnerSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	InnerSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	InnerSphere->SetupAttachment(MeshComp);

	//Create Outer Sphere
	OuterSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphere"));
	OuterSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	OuterSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	OuterSphere->SetupAttachment(MeshComp);

}

// Called every frame
void ABlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Destruction(InnerSphere);
	Attract(OuterSphere);
}

void ABlackhole::Destruction(USphereComponent* Sphere)
{
	//Get all components inside the sphere
	TArray<UPrimitiveComponent*> OverlappingComponents;
	Sphere->GetOverlappingComponents(OverlappingComponents);


	bool bSomethingHasBeenDestroyed = false;
	//Destroy the owners
	for (auto CurrentComponent : OverlappingComponents)
	{
		if (AActor* Owner = CurrentComponent->GetOwner())
		{
			//Avoid interfere with the main component
			if (Owner != MeshComp->GetOwner())
			{
				Owner->Destroy();
				bSomethingHasBeenDestroyed = true;
			}
		}
	}
}

void ABlackhole::Attract(USphereComponent* Sphere)
{
	//Get all components inside the sphere
	TArray<UPrimitiveComponent*> OverlappingComponents;
	Sphere->GetOverlappingComponents(OverlappingComponents);

	//Apply force towards the actor location
	for (auto CurrentComponent : OverlappingComponents)
	{
		AActor* Owner = CurrentComponent->GetOwner();
		if (Owner && CurrentComponent->IsSimulatingPhysics())
		{
			//Avoid interfere with the main component
			if (Owner != MeshComp->GetOwner())
			{
				/*FVector ForceDir = GetActorLocation() - Owner->GetActorLocation();
				CurrentComponent->AddForce(ForceDir * ForceApplied);*/
				CurrentComponent->AddRadialForce(GetActorLocation(), OuterSphere->GetScaledSphereRadius(), -ForceApplied, ERadialImpulseFalloff::RIF_Constant, true);
			}
		}
	}
}

