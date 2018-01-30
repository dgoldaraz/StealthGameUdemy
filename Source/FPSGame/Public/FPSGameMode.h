// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"


//This class handles the global Game Mode we are playing
UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

public:

	AFPSGameMode();

	//Called when the mission is complete
	void CompleteMision(APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMissionCompleted(APawn* InsitgatorPawn);
};



