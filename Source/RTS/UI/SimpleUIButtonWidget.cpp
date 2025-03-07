// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleUIButtonWidget.h"

#include "Components/Button.h"

void USimpleUIButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button->OnClicked.AddDynamic(this, &USimpleUIButtonWidget::OnSimpleUIButtonClickedEvent);
	Button->OnHovered.AddDynamic(this, &USimpleUIButtonWidget::OnSimpleUIButtonHoveredEvent);
	Button->OnUnhovered.AddDynamic(this, &USimpleUIButtonWidget::OnSimpleUIButtonUnHoveredEvent);
}

void USimpleUIButtonWidget::OnSimpleUIButtonClickedEvent()
{
	OnButtonClicked.Broadcast(this, ButtonIndex);
}

void USimpleUIButtonWidget::OnSimpleUIButtonHoveredEvent()
{
	OnButtonHovered.Broadcast(this, ButtonIndex);
}

void USimpleUIButtonWidget::OnSimpleUIButtonUnHoveredEvent()
{
	OnButtonUnHovered.Broadcast(this, ButtonIndex);
}
