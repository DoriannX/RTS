// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTS/AIData.h"
#include "SAIController.generated.h"


class ARTSCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReachedDestinationDelegate, const FCommandData, CommandData);

/**
 * 
 */
UCLASS()
class RTS_API ASaiController : public AAIController
{
	GENERATED_BODY()

public:
	ASaiController(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void CommandMove(const FCommandData& CommandData);
	

	UPROPERTY()
	FReachedDestinationDelegate OnReachedDestination;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UPROPERTY()
	ARTSCharacter* OwningCharacter;

	UPROPERTY()
	FCommandData CurrentCommandData;
};
