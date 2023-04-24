// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/Undegard_MainMenuButton.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

UUndegard_MainMenuButton::UUndegard_MainMenuButton() {
	CheckFocusRate = 0.1f;
}

void UUndegard_MainMenuButton::Start()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_CheckFocus,this,&UUndegard_MainMenuButton::CheckFocus,CheckFocusRate,true);
}

void UUndegard_MainMenuButton::CheckFocus()
{
	if (IsHovered())
	{
		//This button is affected by mouse.
		SetKeyboardFocus();
		SetButtonStyle(EUndegard_ButtonStyleType::ButtonStyleType_Mouse);
	}
	else 
	{
	//Check if the keyboard or gamepad is on me.
		EUndegard_ButtonStyleType StyleTypeSelected = HasKeyboardFocus() ? EUndegard_ButtonStyleType::ButtonStyleType_KeySelected : EUndegard_ButtonStyleType::ButtonStyleType_KeyNotSelected;
		SetButtonStyle(StyleTypeSelected);
	}
}

void UUndegard_MainMenuButton::SetButtonStyle(EUndegard_ButtonStyleType NewStyleType)
{
	BP_SetButtonStyle(NewStyleType);
}

void UUndegard_MainMenuButton::PlayButtonFocusSound(USoundCue* FocusSoundCue)
{
	if (!IsValid(FocusSoundCue))
	{
		return;
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), FocusSoundCue);
	}
}

void UUndegard_MainMenuButton::PlaySelectedButtonSound(USoundCue* SelectedSoundCue)
{
	if (!IsValid(SelectedSoundCue))
	{
		return;
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SelectedSoundCue);
	}
}
