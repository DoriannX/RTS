// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTSCharacter.h"

#include "AIData.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

ARTSCharacter::ARTSCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	CharacterMoveComp = GetCharacterMovement();
	if (CharacterMoveComp)
	{
		CharacterMoveComp->bOrientRotationToMovement = true; // Rotate character to moving direction
		CharacterMoveComp->RotationRate = FRotator(0.f, 640.f, 0.f);
		CharacterMoveComp->bConstrainToPlane = true;
		CharacterMoveComp->bSnapToPlaneAtStart = true;
		MaxSpeed = CharacterMoveComp->MaxWalkSpeed;
	}

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ARTSCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ShouldOrientate)
	{
		SetOrientation(DeltaSeconds);

		if (IsOrientated())
		{
			ShouldOrientate = 0;
		}
	}
}

void ARTSCharacter::Select()
{
	Selected = true;
	HighLight(Selected);
}

void ARTSCharacter::DeSelect()
{
	Selected = false;
	HighLight(Selected);
}

void ARTSCharacter::HighLight(const bool HighLight)
{
	TArray<UPrimitiveComponent*> Components;
	GetComponents<UPrimitiveComponent>(Components);
	for (UPrimitiveComponent* VisualComp : Components)
	{
		if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
		{
			Prim->SetRenderCustomDepth(HighLight);
		}
	}
}

void ARTSCharacter::CommandMoveToLocation(const FCommandData CommandData)
{
	switch (CommandData.Type)
	{
	case CommandMoveSlow:
		{
			SetWalk();
			break;
		}
	case CommandMoveFast:
		{
			SetSprint();
			break;
		}
	case CommandMoveAttack:
		{
		}
	default:
		{
			SetRun();
		}
	}

	//Request AI move
	CommandMove(CommandData);
}

void ARTSCharacter::CommandMove(const FCommandData CommandData)
{
	//Clear delegate to remove any current move in progress
	if (!SAIController)
	{
		return;
	}
	SAIController->OnReachedDestination.Clear();
	SAIController->OnReachedDestination.AddDynamic(this, &ARTSCharacter::DestinationReached);
	SAIController->CommandMove(CommandData);
}

void ARTSCharacter::DestinationReached(const FCommandData CommandData)
{
	TargetOrientation = CommandData.Rotation;
	ShouldOrientate = 1;
}

void ARTSCharacter::SetWalk() const
{
	if (CharacterMoveComp)
	{
		CharacterMoveComp->MaxWalkSpeed = MaxSpeed * .5f;
	}
}

void ARTSCharacter::SetRun() const
{
	if (CharacterMoveComp)
	{
		CharacterMoveComp->MaxWalkSpeed = MaxSpeed;
	}
}

void ARTSCharacter::SetSprint() const
{
	if (CharacterMoveComp)
	{
		CharacterMoveComp->MaxWalkSpeed = MaxSpeed * 1.25f;
	}
}

void ARTSCharacter::SetOrientation(const float DeltaTime)
{
	const FRotator InterpolatedRotation = UKismetMathLibrary::RInterpTo(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 0.f), TargetOrientation, DeltaTime, 2.f); 
	SetActorRotation(InterpolatedRotation);
}

bool ARTSCharacter::IsOrientated() const
{
	const FRotator CurrentRotation = GetActorRotation();
	if (FMath::IsNearlyEqual(CurrentRotation.Yaw, TargetOrientation.Yaw, 0.25f))
	{
		return true;
	}
	return false;
}
