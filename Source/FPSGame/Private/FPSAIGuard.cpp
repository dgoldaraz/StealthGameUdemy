// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "FPSCharacter.h"
#include "Perception/PawnSensingComponent.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PawnSense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	PawnSense->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSense->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotator = GetActorRotation();
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn)
	{
		return;
	}
	SetGuardState(EAIState::Alerted);
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
	//Call mission fail on gameMode
	AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->CompleteMision(SeenPawn, false);
	}
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (GuardState != EAIState::Alerted)
	{
		DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

		const FVector LookAtDirection = (Location - GetActorLocation()).GetSafeNormal();
		FRotator NewLookAt = FRotationMatrix::MakeFromX(LookAtDirection).Rotator();
		NewLookAt.Pitch = 0.0f;
		NewLookAt.Roll = 0.0f;
		SetActorRotation(NewLookAt);

		//Set timer to come back to original rotation
		GetWorldTimerManager().ClearTimer(TimeHandle_ResetOrientation);
		GetWorldTimerManager().SetTimer(TimeHandle_ResetOrientation, this, &AFPSAIGuard::ResetsOrientation, 3.0f);


		SetGuardState(EAIState::Suspicious);
	}
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState != NewState)
	{
		GuardState = NewState;
		OnStateChange(GuardState);
	}
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSAIGuard::ResetsOrientation()
{
	SetActorRotation(OriginalRotator);
	if (GuardState != EAIState::Alerted)
	{
		SetGuardState(EAIState::Idle);
	}
}

