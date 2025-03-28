// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"

class ASPlayerController;
class UFormationSelectorWidget;
/**
 * 
 */
UCLASS(Abstract)
class RTS_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UFormationSelectorWidget* FormationSelectionWidget;

protected:
	UFUNCTION()
	void SetFormationSelectionWidget(const bool bEnabled) const;

	UFUNCTION()
	void OnSelectionUpdated();

	UPROPERTY()
	ASPlayerController* SPlayer;
};
