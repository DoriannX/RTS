// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIdata.generated.h"

UENUM(BlueprintType)
enum ECommandType
{
	CommandMove,
	CommandMoveFast,
	CommandMoveSlow,
	CommandMoveAttack
};

UENUM(BlueprintType)
enum EFormation
{
	Line	UMETA(DisplayName =" Line Formation"),
	Column,
	Wedge,
	Blob
};

USTRUCT(BlueprintType)
struct FCommandData
{
	GENERATED_BODY()
	FCommandData() : SourceLocation(FVector::ZeroVector), Location(FVector::ZeroVector),  Rotation(FRotator::ZeroRotator), Type(CommandMove), Target(nullptr) {}
	FCommandData(const FVector& InLocation, const FRotator& InRotation, const ECommandType InType, AActor* InTarget = nullptr)
		: SourceLocation(InLocation), Location(InLocation), Rotation(InRotation), Type(InType), Target(InTarget) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector SourceLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Location;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator Rotation;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ECommandType> Type;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* Target;
};
