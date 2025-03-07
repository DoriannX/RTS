// Fill out your copyright notice in the Description page of Project Settings.


#include "SAIController.h"

#include "RTS/RTSCharacter.h"

ASaiController::ASaiController(const FObjectInitializer& ObjectInitializer)
{
	
}

void ASaiController::CommandMove(const FCommandData& CommandData)
{
	CurrentCommandData = CommandData;

	MoveToLocation(CommandData.Location);
}

void ASaiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Set a reference to the owner and set a reference of this controller on the owner
	OwningCharacter = Cast<ARTSCharacter>(InPawn);
	if (OwningCharacter)
	{
		OwningCharacter->SetAIController(this);
	}
}

void ASaiController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	OnReachedDestination.Broadcast(CurrentCommandData);
}
