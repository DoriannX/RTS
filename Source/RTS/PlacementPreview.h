// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSCharacter.h"
#include "GameFramework/Actor.h"
#include "PlacementPreview.generated.h"

UCLASS()
class RTS_API APlacementPreview : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlacementPreview();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement")
	TSubclassOf<ARTSCharacter> PlaceableClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
