// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "AIData.h"
#include "Selectable.h"
#include "AI/SAIController.h"
#include "GameFramework/Character.h"
#include "RTSCharacter.generated.h"


UCLASS(Blueprintable)
class ARTSCharacter : public ACharacter, public ISelectable
{
	GENERATED_BODY()

public:
	ARTSCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	/** ISelctable Interface **/
	virtual void Select() override;
	virtual void DeSelect() override;
	virtual void HighLight(const bool HighLight) override;
	/** End of ISelectable Interface **/

	UPROPERTY()
	bool Selected;

	/** Command Functions **/
public:
	UFUNCTION()
	void CommandMoveToLocation(const FCommandData CommandData);

	UFUNCTION()
	void SetAIController(ASaiController* NewAIController) {SAIController = NewAIController;}
protected:
	UFUNCTION()
	void CommandMove(const FCommandData CommandData);

	UFUNCTION()
	void DestinationReached(const FCommandData CommandData);
	
	UFUNCTION()
	void SetWalk() const;

	UFUNCTION()
	void SetRun() const;

	UFUNCTION()
	void SetSprint() const;

	UFUNCTION()
	void SetOrientation(const float DeltaTime);

	UFUNCTION()
	bool IsOrientated() const;

	UPROPERTY()
	UCharacterMovementComponent* CharacterMoveComp;

	UPROPERTY()
	float MaxSpeed;

	UPROPERTY()
	FRotator TargetOrientation;

	UPROPERTY()
	uint8 ShouldOrientate;

	UPROPERTY()
	ASaiController* SAIController;
	
	/** End Command Functions **/
	
};

