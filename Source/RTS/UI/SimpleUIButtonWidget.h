// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimpleUIButtonWidget.generated.h"

class UTextBlock;
class UImage;
class UButton;
class USimpleUIButtonWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FButtonClicked, USimpleUIButtonWidget*, Button, int, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FButtonHovered, USimpleUIButtonWidget*, Button, int, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FButtonUnHovered, USimpleUIButtonWidget*, Button, int, Index);
/**
 * 
 */
UCLASS()
class RTS_API USimpleUIButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ButtonImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ButtonText;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FButtonClicked OnButtonClicked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FButtonClicked OnButtonHovered;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FButtonClicked OnButtonUnHovered;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	int32 ButtonIndex;

protected:
	UFUNCTION()
	void OnSimpleUIButtonClickedEvent();
	
	UFUNCTION()
	void OnSimpleUIButtonHoveredEvent();

	UFUNCTION()
	void OnSimpleUIButtonUnHoveredEvent();
	
};
