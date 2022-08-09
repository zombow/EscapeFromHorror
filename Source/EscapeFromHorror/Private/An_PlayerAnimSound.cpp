// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerAnimSound.h"
#include "Kismet/GameplayStatics.h"

void UAn_PlayerAnim::WalkSoundPlay()
{
	UGameplayStatics::PlaySound2D(this, walkSound);
}

void UAn_PlayerAnim::RunSoundPlay()
{
	UGameplayStatics::PlaySound2D(this, runSound);
}

void UAn_PlayerAnim::CrouchSoundPlay()
{
	UGameplayStatics::PlaySound2D(this, crouchSound);
}

void UAn_PlayerAnim::JumpSoundPlay()
{
	UGameplayStatics::PlaySound2D(this, jumpSound);
}

void UAn_PlayerAnim::RandSoundPlay()
{
	UGameplayStatics::PlaySound2D(this, randSound);
}
