// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputActions.h"
#include "PlayerInputActions.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSelectedUpdatedDelegate);

/**
 * 
 */
UCLASS()
class RTS_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;

	UFUNCTION()
	void Handle_Selection(AActor* ActorToSelect);
	void Handle_Selection(TArray<AActor*> ActorsToSelect);
	
	UFUNCTION()
	void Handle_DeSelection(AActor* ActorToSelect);
	void Handle_DeSelection(TArray<AActor*> ActorsToSelect);

	UFUNCTION()
	FVector GetMousePositionOnTerrain() const;

	UFUNCTION()
	FVector GetMousePositionOnSurface() const;

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	bool ActorSelected(AActor* ActorToCheck) const;

	UFUNCTION(Server, Reliable)
	void Server_Select(AActor* ActorToSelect);

	UFUNCTION(Server, Reliable)
	void Server_Select_Group(const TArray<AActor*>& ActorsToSelect);

	UFUNCTION(Server, Reliable)
	void Server_DeSelect(AActor* ActorToDeselect);
	
	UFUNCTION(Server, Reliable)
	void Server_DeSelect_Group(const TArray<AActor*>& ActorsToDeSelect);

	UFUNCTION(Server, Reliable)
	void Server_ClearSelected();

	UFUNCTION()
	void OnRep_Selected();

	UPROPERTY(ReplicatedUsing = OnRep_Selected)
	TArray<AActor*> Selected;

	UPROPERTY()
	FSelectedUpdatedDelegate OnSelectedUpdated;

	/** Enhanced Input **/

public:
	UFUNCTION()
	void AddInputMapping(const UInputMappingContext* InputMapping, const int32 MappingPriority = 0) const;

	UFUNCTION()
	void RemoveInputMapping(const UInputMappingContext* InputMapping) const;

	UFUNCTION()
	void SetInputDefault(const bool Enabled = true) const;

	UFUNCTION()
	void SetInputPlacement(const bool Enabled = true) const;

	UFUNCTION()
	void SetInputShift(const bool Enabled = true) const;

	UFUNCTION()
	void SetInputAlt(const bool Enabled = true) const;

	UFUNCTION()
	void SetInputCtrl(const bool Enabled = true) const;

	UFUNCTION()
	UDataAsset* GetInputActionsAsset() const { return PlayerActionsAsset; }

protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player Settings")
	UDataAsset* PlayerActionsAsset;

	/** Placement **/
public:
	UFUNCTION()
	bool IsPlacementModeEnabled() const { return bPlacementModeEnabled;}

	UFUNCTION()
	void SetPlacementPreview();

	UFUNCTION()
	void Place();
	
	UFUNCTION()
	void PlaceCanceled();

protected:
	UFUNCTION()
	void UpdatePlacement() const;
	
	UFUNCTION(Server, Reliable)
	void Server_Place(AActor* PlacementPreviewToSpawn);

	UFUNCTION(Client, Reliable)
	void EndPlacement();
	
	UPROPERTY()
	bool bPlacementModeEnabled;

	UPROPERTY()
	AActor* PlacementPreviewActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Placeable")
	TSubclassOf<AActor> PreviewActorType;
};
