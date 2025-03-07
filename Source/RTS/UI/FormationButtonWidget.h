// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleUIButtonWidget.h"
#include "RTS/AIData.h"
#include "FormationButtonWidget.generated.h"
/**
 * 
 */
UCLASS()
class RTS_API UFormationButtonWidget : public USimpleUIButtonWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	TEnumAsByte<EFormation> Formation;
	
};
